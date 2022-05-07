#include "my_transform.hpp"
#include <string>
#include <iostream>
#include <cstring>
#include "Provider_BWCAfromIMPRgivenDSLC_DaysSinceLastCheck.hpp"
#include <fstream>

// We are wrapping this in an extern "C" so that the transform_kaggle2imdb function
// is callable as C code.
extern "C" {

// This needs a forward reference for the compiler to be happy. Often this is
// done in a header file that the user would include in their code to provide
// the definition of the function.
int transform_impr2bwca(void *msg1, void *msg2);
//void *create_and_populate_kaggle_msg(OneToFiveReviews::KReviewRating::EnumItem KaggleReviewerRating);
void *create_and_populate_impr_msg(double ilat, double ilong, double mlat, double mlong);
const char* return_bwca(void *msg);
void free_impr_msg(void *msg) ;
void *create_bwca_msg();
void free_bwca_msg(void *msg);

//this function creates and populates the impr message to be transformed
void *create_and_populate_impr_msg(double ilat, double ilong, double mlat, double mlong) {
    IanMarkPosition::IanMarkPositionMessage *imprMsg = new IanMarkPosition::IanMarkPositionMessage;
    // std::cout << "Ian Latitude" << std::endl;
    // std::cout << "     " << ilat << std::endl;
    // std::cout << "Ian Longitude" << std::endl;
    // std::cout << "     " << ilong << std::endl;
    // std::cout << "Mark Latitude" << std::endl;
    // std::cout << "     " << ilat << std::endl;
    // std::cout << "Mark Longitude" << std::endl;
    // std::cout << "     " << ilong << std::endl;   
    
    
    imprMsg->setIanLat(ilat);
    imprMsg->setIanLong(ilong);
    imprMsg->setMarkLat(mlat);
    imprMsg->setMarkLong(mlong);

    // std::cout << "I am trying to open file" << std::endl;
    // std::fstream newfile;
    // newfile.open("/media/sf_toy_movies/golfcart_out_25_Apr_2022/transform/output3.txt",std::ios::in);
    // if (newfile.is_open()) {
    //     std::cout << "file is open" << std::endl;
    //     std::string tp;
    //     while(getline(newfile, tp)) {
    //         std::cout << tp << std::endl;
    //     }
    //     newfile.close();
    //     try {
    //         int my_number = std::stoi(tp);
    //         std::cout << my_number << std::endl;
    //     }
    //     catch(std::exception& e) {
    //         std::cout << "error converting" << std::endl;
    //     }
    //     //int my_number = std::stoi(tp);
    //     //std::cout << my_number << std::endl;
    // }
    // else {
    //     std::cout << "failed to open file\n:" << std::endl;
    // }


    //if you want to see results uncomment code below
    //std::cout << "Ian Latitude" << std::endl;
    //std::cout << "     " << ilat << std::endl;

    return imprMsg;
}

//create bwca message
void *create_bwca_msg() {
    BatteryWaterCheck::CheckStatusMessage *bwcaMsg = new BatteryWaterCheck::CheckStatusMessage;
    return bwcaMsg;
}

// This is a callable C-named function that transforms the message pointed to
// by msg1 (kaggle message) into the message pointed to by msg2 (imdb message)
int transform_impr2bwca(void *msg1, void *msg2) {

    // The transform function requires messages to be wrapped in a
    // std::shared_ptr, which is a reference counted wrapper that will, by
    // default, delete the resource when it goes out of scope. We don't want
    // that here since the message is owned by the caller so we supply custom
    // "deleter" C++ lambdas that do nothing
    std::shared_ptr<IanMarkPosition::IanMarkPositionMessage> spImprMsg(
        (IanMarkPosition::IanMarkPositionMessage *) msg1, [](void *){});
    std::shared_ptr<BatteryWaterCheck::CheckStatusMessage> spBwcaMsg(
        (BatteryWaterCheck::CheckStatusMessage *) msg2, [](void *){});   

    // These are the contextual parameters, which are obtained from
        // dedicated provider classes. It may be necessary to populate
        // each provider class specified. Please see the classes defined
        // in the files named "Provider_X" where X is the namespace and
        // type name for the contextual parameter.
    Provider_BWCAfromIMPRgivenDSLC_DaysSinceLastCheck dslcInfoProvider;
    BWCAfromIMPRgivenDSLC::DaysSinceLastCheck dslcInfo = dslcInfoProvider.get();

    // call the transform function
    try {
        my_transform::execute(*spImprMsg, *spBwcaMsg, dslcInfo);
    } catch (...) {
        // failed due to exception
        return -1;
    }
    //if you want to see results uncomment code below
    //std::string BWCAresult = (*spBwcaMsg).getCheckAssignmentString();
    //std::cout << "Battery Water Check Assignment" << std::endl;
    //std::cout << "    " << BWCAresult << std::endl;
    //std::basic_ostream << *spBwcaMsg << "\n";    

    return 0;
}

//this function returns the battery water check assignment
const char* return_bwca(void *msg) {
    BatteryWaterCheck::CheckStatusMessage *the_bwcaMsg = (BatteryWaterCheck::CheckStatusMessage *) msg;
    std::string myc_string = (*the_bwcaMsg).getCheckAssignmentString();
    const char* theBWCAassignment = myc_string.c_str();
    //if you want to see results uncomment code below
    //std::cout << "IMDB Review" << std::endl;
    //std::cout << "    " << theIMDBReviewerRating << std::endl;
    return theBWCAassignment;
}

//free kaggle message after use
void free_impr_msg(void *msg) {
    IanMarkPosition::IanMarkPositionMessage *imprMsg =
        (IanMarkPosition::IanMarkPositionMessage *) msg;
    delete imprMsg;
}

//free imdb message after use
void free_bwca_msg(void *msg) {
    BatteryWaterCheck::CheckStatusMessage *bwcaMsg =
        (BatteryWaterCheck::CheckStatusMessage *) msg;
    delete bwcaMsg;
}

}