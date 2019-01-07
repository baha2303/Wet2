//
// Created by baha2 on 1/2/2019.
//

#include "library.h"
#include "ImageTagger.h"
void * Init(int pixels) {
    if(pixels<=0) return nullptr;
    try {
        ImageTagger* sys = new ImageTagger(pixels);
        return (void*)sys;
    } catch (...) {
        return nullptr;
    }
}

StatusType AddImage(void *DS, int imageID) {

    if(!DS || imageID <=0 )
        return INVALID_INPUT;
    ImageTagger* IT = static_cast<ImageTagger*>(DS) ;
    return IT->addImage(imageID);

}


StatusType DeleteImage(void *DS, int imageID) {

    if(!DS || imageID <=0 )
        return INVALID_INPUT;
    ImageTagger* IT = static_cast<ImageTagger*>(DS) ;
    return IT->deleteImage(imageID);
}


StatusType SetLabelScore(void *DS, int imageID, int pixel, int label, int score) {
    if(!DS )
        return INVALID_INPUT;
    ImageTagger* IT = static_cast<ImageTagger*>(DS) ;
if( imageID <=0 || pixel<0 || pixel >= IT->pixels || score<=0 || label<=0) return INVALID_INPUT;
    return (IT->SetLabelScore(imageID,pixel,label,score));
}


StatusType ResetLabelScore(void *DS, int imageID, int pixel, int label) {

    if(!DS )
        return INVALID_INPUT;
    ImageTagger* IT = static_cast<ImageTagger*>(DS) ;
    if( imageID <=0 || pixel<0 || pixel >= IT->pixels ||  label<=0) return INVALID_INPUT;
    return (IT->ResetLabelScore(imageID,pixel,label));
}

/* Description:   Gets the highest scored label of a the super pixel containing the given pixel in an image.
 * Input:         DS - A pointer to the data structure.
 *                imageID - The image to get the label from.
 * 				  pixel - The pixel of the super pixel to get the label from.
 * 				  label - A pointer to a variable which will hold the label.
 * Output:        The highest scored label in the super pixel containing pixel.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If DS==NULL pixel >= pixels or pixel < 0 or imageID < 0 or label == NULL.
 *                FAILURE - If the image does not exist in the DS, or the super pixel is not tagged at all.
 *                SUCCESS - Otherwise.
 */
StatusType GetHighestScoredLabel(void *DS, int imageID, int pixel, int *label) {

    if(!DS || !label)
        return INVALID_INPUT;
    ImageTagger* IT = static_cast<ImageTagger*>(DS) ;
    if( imageID <=0 || pixel<0 || pixel >= IT->pixels ) return INVALID_INPUT;
    return (IT->GetHighestScoredLabel(imageID,pixel,label));
}


/* Description:   Merges two super pixels in to one super pixel
 * Input:         DS - A pointer to the data structure.
 *                imageID - The image to get the segments from.
 *				  pixel1 - The pixel of the first super pixel to merge.
 *				  pixel2 - The pixel of the second super pixel to merge.
 * Output:        None.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If DS==NULL imageID <= 0 pixel1 < 0 pixel1 >= pixels pixel2 < 0 pixel2 >= pixels.
 *                FAILURE - If the image does not exist in the DS or if the two pixel belong to the same super pixel.
 *                SUCCESS - Otherwise.
 */
StatusType MergeSuperPixels(void *DS, int imageID, int pixel1, int pixel2) {

    if(!DS )
        return INVALID_INPUT;
    ImageTagger* IT = static_cast<ImageTagger*>(DS) ;
    if( imageID <=0 || pixel1<0 || pixel1 >= IT->pixels || pixel2<0 || pixel2 >= IT->pixels) return INVALID_INPUT;

    return (IT->MergeSuperPixels(imageID,pixel1,pixel2));
}

/* Description:   Quits and deletes the database.
 *                DS should be set to NULL.
 * Input:         DS - A pointer to the data structure.
 * Output:        None.
 * Return Values: None.
 */
void Quit(void** DS) {
    ImageTagger* IT = static_cast<ImageTagger*>(*DS) ;
    delete(IT);
    *DS= NULL;
    return;
}


