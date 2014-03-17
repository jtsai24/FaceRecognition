#ifndef FACEDETECT_H_
#define FACEDETECT_H_

#include <string>

/*
 *  Using openCV to process image, 
 *  create a new image and save it locally
 *. Send the path of the new image.
 * 
 *  Argument: 
 *  orgImFilePath: image file stored locally
 *  
 *  Output:
 *  file path of the image created. 
**/

string faceDetect (string orgImgFilePath);

#endif