#include <stdio.h>
#include <opencv2/opencv.hpp>

#define CV_RGB2GRAY cv::COLOR_RGB2GRAY
#define CV_WINDOW_AUTOSIZE cv::CV_WINDOW_AUTOSIZE



// function to change rgb image to grayscale image
cv::Mat rgb2Gray(cv:: Mat image, int H, int W) {
	// Initialize an empty grayscale image (8-bit unsigned integer matrix with one channel)
    cv::Mat imageGray(H, W, CV_8UC1);

    // Loop through the pixels of the image
    for (int r = 0; r < H; r++)
    {
        for (int c = 0; c < W; c++)
        {
            // Retrieve the pixel from location (r, c)
            cv::Vec3b pix = image.at<cv::Vec3b>(r, c);
            
            // Apply formula to get the grayscale value and assign it to imageGray
            uint8_t res = 0.2989 * pix[2] + 0.5871 * pix[1] + 0.1140 * pix[0];
            imageGray.at<uint8_t>(r, c) = res;
        }
    }

    return imageGray;
}



int main(int argc, char* argv[]) {
    // error check
    if ( argc != 2 )
    {
        printf("usage: ./transform <input_color_image_filename>\n");
        return -1;
    }
    
    // create image variable & read in user input
    cv::Mat image;
    image = cv::imread( argv[1], 1 );

    // if the user input is invalid, error check
    if ( !image.data )
    {
        printf("No image data \n");
        return -1;
    }

    // displays the input image
    cv::imshow("Input Image", image);
    cv::waitKey(0);
	


// 1) Translate by (tx, ty) (10 points)
    int randX = rand()%(10) - 5;
    int randY = rand()%(10) - 5;
    float tx = float(image.size[0]) / randX;
    float ty = float(image.size[1]) / randY;

    // create the translation matrix using tx and ty
    float warp_values[] = { 1.0, 0.0, tx, 0.0, 1.0, ty };
    cv::Mat translation_matrix = cv::Mat(2, 3, CV_32F, warp_values);

    cv::Mat translated_image;
    warpAffine(image, translated_image, translation_matrix, image.size());

    cv::imshow("Translated Image", translated_image);
    cv::waitKey(0);



// 2) Crop and Scale/Resize, upper left crop location and crop region size (15 points)
    int randWidth = rand()%(600) - 20;
    int randHeight = rand()%(600) - 20;

    cv::Mat resized;
    resize(image, resized, cv::Size(randWidth, randHeight), cv::INTER_LINEAR);

    // crop the image
    cv::Mat crop = resized(cv::Range(50,randHeight),cv::Range(50,randWidth)); 

    // Display the cropped image    
    cv::imshow("Resized and Cropped Image", crop);
    cv::waitKey(0);



// 3) Vertical-Flip about y-axis (10 points)
    cv::Mat verticalFlip;
    flip(image,verticalFlip,1);

    // Display the flipped image    
    cv::imshow("Flipped about Y Axis", verticalFlip);
    cv::waitKey(0);



// 4) Horizontal-Flip about x-axis (5 points)
    cv::Mat horizontalFlip;
    flip(image,horizontalFlip,0);

    // Display the flipped image    
    cv::imshow("Flipped about X Axis", horizontalFlip);
    cv::waitKey(0);



// 5) Rotate by five random angles between -180 deg to +180 deg (15 points)
    int randRotation = rand()%(180) - 180;
    cv::Point2f center((image.cols - 1) / 2.0, (image.rows - 1) / 2.0);
    cv::Mat rotation_matix = getRotationMatrix2D(center, randRotation, 1.0);
    cv::Mat rotated_image;
    warpAffine(image, rotated_image, rotation_matix, image.size());

    // Display the rotated image    
    cv::imshow("Rotated Image", rotated_image);
    cv::waitKey(0);



// 7a) Random intensity stretch for grayscale and 
    //intensity stretch for grayscale
    cv::Mat grayscaleImage = rgb2Gray(image, image.size[0], image.size[1]);

    int randIntensityValue = rand()%(255) - 100;
    grayscaleImage.convertTo(grayscaleImage, -1, 1, randIntensityValue);

    cv::imshow("Contrasted w Intensity Stretch Image", grayscaleImage);
    cv::waitKey(0);

// 7b) contrast stretch one or more channels in RGB images
    //randomly generated contrast
    float randContrast = -1 + (float)(rand()) /((float)(RAND_MAX/(8)));
    cv::Mat contrastPic;
    image.convertTo(contrastPic, -1, randContrast, 0); //increase the contrast by 2

    cv::imshow("Contrasted Image", contrastPic);
    cv::waitKey(0);



// 8) Blurring using local averaging, use a box filter (all ones) of three sizes: 3x3, 5x5, 7x7 (15 points)
    int randNumber = rand()%(3);
    if(randNumber % 3 == 0) {
        cv::Mat blurredImage3;
        blur(image,blurredImage3,cv::Size(3,3));

        cv::imshow("Blurred Image 3x3", blurredImage3);
        cv::waitKey(0);
    }
    else if(randIntensityValue % 3 == 1) {
        cv::Mat blurredImage5;
        blur(image,blurredImage5,cv::Size(5,5));

        cv::imshow("Blurred Image 5x5", blurredImage5);
        cv::waitKey(0);
    }
    else {
        cv::Mat blurredImage7;
        blur(image,blurredImage7,cv::Size(7,7));

        cv::imshow("Blurred Image 7x7", blurredImage7);
        cv::waitKey(0);
    }



// 6) Randomly erase three (small) rectangular regions in the original image each at a different location and size (15 points)
    cv::Mat randomErase = image;

    for(int i=0; i<3; i++) {
        int randStartPointX = rand()%(randomErase.size[0]) + 1;
        int randStartPointY = rand()%(randomErase.size[1]) + 1;
        int randW = rand()%(30) + 10;
        int randH = rand()%(30) + 10;

        for(int r=randStartPointX; r<randStartPointX + randW && r < randomErase.size[0]; r++) {
            for(int c = randStartPointY; c<randStartPointY + randH && c < randomErase.size[1]; c++) {
                randomErase.at<uint8_t>(r,c) = 0;
            }
        }
    }

    cv::imshow("Deleted Areas Image", randomErase);
    cv::waitKey(0);
}