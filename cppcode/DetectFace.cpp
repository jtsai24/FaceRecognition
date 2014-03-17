#include <cv.h>
#include <highgui.h>
#include <stdlib.h>
#include <cerrno>
#include <iostream>
#include <stdio.h>  /* defines FILENAME_MAX */
#ifdef WINDOWS
    #include <direct.h>
    #define GetCurrentDir _getcwd
#else
    #include <unistd.h>
    #define GetCurrentDir getcwd
 #endif
#include <string>
using namespace std;
const char * cascade_name = "haarcascade_frontalface_alt.xml";
/*
+ *  Using openCV to process image,
+ *  create a new image and save it locally
+ *. Send the path of the new image.
+ *
+ *  Argument:
+ *  orgImFilePath: image file stored locally
+ *
+ *  Output:
+ *  file path of the image created.
+**/


string faceDetect (string orgImgFilePath)
{
    char cCurrentPath[FILENAME_MAX];

     if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))
         {
         return "error";
         }

    cCurrentPath[sizeof(cCurrentPath) - 1] = '\0'; /* not really required */

    printf ("The current working directory is %s", cCurrentPath);
    //---------------------------------------------------------------------
    string processed_file_loc;
    CvSize minFeatureSize = cvSize(20, 20);
	// Only search for 1 face.
	//int flags = CV_HAAR_FIND_BIGGEST_OBJECT | CV_HAAR_DO_ROUGH_SEARCH;
	int flags = 0;
	// How detailed should the search be.
	float search_scale_factor = 1.1f;
	//---------------------------------------------------------------------
    /* Load the classifier data from the .xml file */
    CvHaarClassifierCascade* cascade = (CvHaarClassifierCascade*)cvLoad( cascade_name);
    /* create a window with handle result */
    cvNamedWindow("result");
    /* read the input image */
    IplImage* image = cvLoadImage( orgImgFilePath.c_str(), 1 );

    IplImage* gray = cvCreateImage( cvSize(image->width,image->height), 8, 1 );
    /* now convert the input image into b&w and store it in the placeholder */
    cvCvtColor( image, gray, CV_BGR2GRAY );
    /* create memory storage to be used by cvHaarDetectObjects */
    CvMemStorage* storage = cvCreateMemStorage();
    //---------------------------------------------------------------------
    CvSeq* faces;
    cvClearMemStorage(storage);

    /* used cvHaarDetectObjects */
    /* 8-bit depth RGB representation of color red */
    static  CvScalar RED = {0, 0, 255};

    faces = cvHaarDetectObjects(gray, cascade, storage, search_scale_factor, 3, flags, minFeatureSize);
    if (faces->total > 0)
    {
        printf("%d face detected\n;",faces->total);
    }else
    {
        printf("no face detected\n");
    }


    /* go through all the detected faces, and draw them into the input image */
    for( int i = 0; i < (faces ? faces->total: 0); i++)
    {
        CvRect *r = (CvRect*)cvGetSeqElem( faces, i );
        CvPoint ul; CvPoint lr;
        ul.x = r->x; ul.y = r->y;
        lr.x = r->x + r->width; lr.y = r->y + r->height;
        /* draws a rectangle with given coordinates of the upper left
        and lower right corners into an image */
        cvRectangle(image, ul, lr, RED, 3, 8, 0);
    }

    /* free up the memory */
    cvReleaseImage( &gray );
    /* show the result and wait for a keystroke form user before finishing */
    cvShowImage("result", image );
    cv::Mat newC = cv::cvarrToMat(image);
    char test[] = "test.jpg";
    cv::imwrite(test,newC);
    cvWaitKey(0);
    cvReleaseImage( &image );
    cvDestroyWindow("result");
    processed_file_loc = cCurrentPath;
    processed_file_loc = processed_file_loc + "/bin/Debug/processed_image.jpg";
    printf("\n  new picture location = %s \n;",processed_file_loc.c_str());
    return processed_file_loc;
}

//const char * cascade_name = "wii_frontalface4.xml";

//const char * cascade_name = "haarcascade_frontalface_default.xml";
int main (int argc,  const char * argv[] )
{
    string processed_file_str;
    string input_file_str;

    input_file_str = argv[1];
    processed_file_str = faceDetect(argv[1]);
    return 0;
}




