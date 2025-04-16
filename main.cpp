#include <opencv2/dnn.hpp>       // Deep Neural Network module
#include <opencv2/imgproc.hpp>   // Image processing
#include <opencv2/highgui.hpp>   // High-level GUI (windowing, image display)
#include <opencv2/core/utils/logger.hpp> // For disabling OpenCV logs if needed
#include <iostream>             // Standard input/output stream

int main(int argc, char** argv) {
    // Optional: Suppress unnecessary OpenCV informational logs
    cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_WARNING);

    // --- Configuration ---
    // Paths to the pre-trained Caffe model files
    // IMPORTANT: Replace these with the ACTUAL paths where you downloaded the files!
    std::string proto_path = "path/to/protoText/deploy.prototxt.txt";
    std::string model_path = "path/to/model/res10_300x300_ssd_iter_140000.caffemodel";

    // Confidence threshold to filter weak detections
    float confidence_threshold = 0.5;

    // --- Load the DNN Model ---
    cv::dnn::Net net;
    try {
        net = cv::dnn::readNetFromCaffe(proto_path, model_path);
    } catch (const cv::Exception& e) {
        std::cerr << "Error loading network files: " << e.what() << std::endl;
        std::cerr << "Please ensure the paths to 'deploy.prototxt.txt' and '*.caffemodel' are correct." << std::endl;
        return -1;
    }

    if (net.empty()) {
        std::cerr << "Failed to load the network. Check file paths and integrity." << std::endl;
        return -1;
    }
    std::cout << "Network loaded successfully." << std::endl;

    // --- Initialize Video Capture ---
    // Use 0 for the default webcam
    cv::VideoCapture cap(0);
    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open video capture device." << std::endl;
        return -1;
    }
    std::cout << "Webcam opened successfully." << std::endl;

    cv::Mat frame;
    while (true) {
        // Capture frame-by-frame
        cap >> frame;
        if (frame.empty()) {
            std::cerr << "Error: Captured empty frame." << std::endl;
            break;
        }

        // --- Preprocess the Frame for the Network ---
        // Get frame dimensions
        int frame_height = frame.rows;
        int frame_width = frame.cols;

        // Create a blob from the frame.
        // This specific model expects 300x300 BGR images.
        // Parameters:
        //   image: input image
        //   scalefactor: multiplier for image values (1.0 means no scaling)
        //   size: target spatial size for output image
        //   mean: scalar with mean values which are subtracted from channels.
        //         Values are intended to be in (B, G, R) order if image is BGR.
        //   swapRB: flag which indicates that swap first and last channels
        //           in 3-channel image is necessary.
        //   crop: flag which indicates whether image will be cropped after resize.
        cv::Mat blob = cv::dnn::blobFromImage(frame, 1.0, cv::Size(300, 300),
                                              cv::Scalar(104.0, 177.0, 123.0),
                                              false, false);

        // --- Perform Face Detection ---
        // Set the blob as input to the network
        net.setInput(blob);

        // Perform a forward pass to get the detection results
        cv::Mat detections = net.forward();

        // The result 'detections' is a 4D matrix:
        //   detections[0, 0, i, 0] - Always 0
        //   detections[0, 0, i, 1] - Class identifier (always 1 for face in this model)
        //   detections[0, 0, i, 2] - Confidence score for the detection
        //   detections[0, 0, i, 3] - x-coordinate of the top-left corner (normalized)
        //   detections[0, 0, i, 4] - y-coordinate of the top-left corner (normalized)
        //   detections[0, 0, i, 5] - x-coordinate of the bottom-right corner (normalized)
        //   detections[0, 0, i, 6] - y-coordinate of the bottom-right corner (normalized)

        // --- Process Detections ---
        cv::Mat detection_matrix(detections.size[2], detections.size[3], CV_32F, detections.ptr<float>());

        for (int i = 0; i < detection_matrix.rows; i++) {
            float confidence = detection_matrix.at<float>(i, 2);

            // Filter out weak detections
            if (confidence > confidence_threshold) {
                // Get normalized coordinates
                float x_left_bottom = detection_matrix.at<float>(i, 3);
                float y_left_bottom = detection_matrix.at<float>(i, 4);
                float x_right_top = detection_matrix.at<float>(i, 5);
                float y_right_top = detection_matrix.at<float>(i, 6);

                // Calculate actual pixel coordinates
                int x1 = static_cast<int>(x_left_bottom * frame_width);
                int y1 = static_cast<int>(y_left_bottom * frame_height);
                int x2 = static_cast<int>(x_right_top * frame_width);
                int y2 = static_cast<int>(y_right_top * frame_height);

                // Ensure coordinates are within frame boundaries
                x1 = std::max(0, x1);
                y1 = std::max(0, y1);
                x2 = std::min(frame_width - 1, x2);
                y2 = std::min(frame_height - 1, y2);

                // Draw bounding box
                cv::rectangle(frame, cv::Point(x1, y1), cv::Point(x2, y2), cv::Scalar(0, 255, 0), 2);

                // Put confidence text
                std::string label = "Face: " + cv::format("%.2f", confidence);
                int base_line;
                cv::Size label_size = cv::getTextSize(label, cv::FONT_HERSHEY_SIMPLEX, 0.5, 1, &base_line);
                cv::rectangle(frame, cv::Point(x1, y1 - label_size.height - base_line),
                              cv::Point(x1 + label_size.width, y1), cv::Scalar(0, 255, 0), cv::FILLED);
                cv::putText(frame, label, cv::Point(x1, y1 - base_line), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 0, 0), 1);
            }
        }

        // --- Display the Result ---
        cv::imshow("Face Detection", frame);

        // Exit loop if 'q' key is pressed
        if (cv::waitKey(1) == 'q') {
            break;
        }
    }

    // --- Cleanup ---
    cap.release();              // Release the video capture object
    cv::destroyAllWindows();    // Close all OpenCV windows

    return 0;
}
