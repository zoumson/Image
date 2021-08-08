#include <iostream>
#include <chrono>


#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

int main ( int argc, char** argv )
{
         
   cv::String keys =
        "{i image |<none>           | input image path}"                 
        "{help h usage ?    |      | show help message}";      
  
    cv::CommandLineParser parser(argc, argv, keys);
    parser.about("Basic opencv image processing");
    if (parser.has("help")) 
    {
        parser.printMessage();
        return 0;
    }
 
    cv::String imagePath = parser.get<cv::String>("image");
    // always after variable, required variable are checked here
    if (!parser.check()) 
    {
        parser.printErrors();
        return -1;
    }    
   
    cv::Mat image = cv::imread (imagePath); // read image from path 

    // Image dimension 
    std::cout<<"Image column"<<image.cols<<",row"<<image.rows<<",channels"<<image.channels()<<"\n";
    cv::imshow ( "image", image );      // Show image to user
    cv::waitKey ( 0 );                  // to see image from window add a wait 
    // Check image type
    if ( image.type() != CV_8UC1 && image.type() != CV_8UC3 )
    {

        std::cout<<"image type not supported."<<"\n";
        return 0;
    }

    // Traverse the image, please note that the following traversal methods 
    // can also be used for random pixel access
    // Use std::chrono to compute the algorithm duration
    std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
    for ( size_t y=0; y<image.rows; y++ )
    {
        // Use cv::Mat::ptr to get the line pointer of the image
        // row_ptr single line pointer to image 
        unsigned char* row_ptr = image.ptr<unsigned char> ( y ); 
        // traverse column
        for ( size_t x=0; x<image.cols; x++ )
        {
            // Access the pixel at x,y
            // data_ptr Point to the pixel data to be accessed
            unsigned char* data_ptr = &row_ptr[ x*image.channels() ]; 
            // Each channel of the output pixel, if it is a grayscale image, 
            // there is only one channel
            for ( int c = 0; c != image.channels(); c++ )
            {
                // data is the value of the c channel of I(x,y)
                unsigned char data = data_ptr[c]; 
            }
        }
    }
    std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
    std::chrono::duration<double> time_used = std::chrono::duration_cast<std::chrono::duration<double>>( t2-t1 );
    std::cout<<"Time to traverse the image："<<time_used.count()<<" second."<<"\n";

    // About the copy of cv::Mat
    // Direct assignment does not copy data
    cv::Mat image_another = image;
    // Modifying image_another will cause the image to change
    // Zero the 100*100 block in the upper left corner
    image_another ( cv::Rect ( 0,0,100,100 ) ).setTo ( 0 );
    cv::imshow ( "image", image );
    cv::waitKey ( 0 );
    
    // Use clone function to copy data
    cv::Mat image_clone = image.clone();
    image_clone ( cv::Rect ( 0,0,100,100 ) ).setTo ( 255 );
    cv::imshow ( "image", image );
    cv::imshow ( "image_clone", image_clone );
    cv::waitKey ( 0 );

    // There are many basic operations for images, such as cutting, rotating, zooming, etc., 
    // which are not introduced one by one due to space limitations.
    // Please refer to the official OpenCV documentation to 
    // find out how to call each function.
    cv::destroyAllWindows();

    return 0;
}
