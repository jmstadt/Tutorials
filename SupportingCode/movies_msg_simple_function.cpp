#include "my_transform.hpp"
#include <string>
#include <iostream>
#include <cstring>

// We are wrapping this in an extern "C" so that the transform_kaggle2imdb function
// is callable as C code.
extern "C" {

// This needs a forward reference for the compiler to be happy. Often this is
// done in a header file that the user would include in their code to provide
// the definition of the function.
int transform_kaggle2imdb(void *msg1, void *msg2);
void *create_and_populate_kaggle_msg(OneToFiveReviews::KReviewRating::EnumItem KaggleReviewerRating);
const char* return_imdb_review(void *msg);
void free_kaggle_msg(void *msg) ;
void *create_imdb_msg();
void free_imdb_msg(void *msg);


//this function creates and populates the kaggle message to be transformed
void *create_and_populate_kaggle_msg(OneToFiveReviews::KReviewRating::EnumItem KaggleReviewerRating) {
    OneToFiveReviews::KaggleMovieReview *kaggleMsg = new OneToFiveReviews::KaggleMovieReview;
    kaggleMsg->setKaggleReviewerRating(KaggleReviewerRating);

    //if you want to see results uncomment code below
    //std::cout << "Kaggle Review" << std::endl;
    //std::cout << "     " << KaggleReviewerRating << std::endl;

    return kaggleMsg;
}

//create imdb message
void *create_imdb_msg() {
    PosNegReviews::IMDBMovieReview *imdbMsg = new PosNegReviews::IMDBMovieReview;
    return imdbMsg;
}

// This is a callable C-named function that transforms the message pointed to
// by msg1 (kaggle message) into the message pointed to by msg2 (imdb message)
int transform_kaggle2imdb(void *msg1, void *msg2) {

    // The transform function requires messages to be wrapped in a
    // std::shared_ptr, which is a reference counted wrapper that will, by
    // default, delete the resource when it goes out of scope. We don't want
    // that here since the message is owned by the caller so we supply custom
    // "deleter" C++ lambdas that do nothing
    std::shared_ptr<OneToFiveReviews::KaggleMovieReview> spKaggleMsg(
        (OneToFiveReviews::KaggleMovieReview *) msg1, [](void *){});
    std::shared_ptr<PosNegReviews::IMDBMovieReview> spImdbMsg(
        (PosNegReviews::IMDBMovieReview *) msg2, [](void *){});   

    // call the transform function
    try {
        my_transform::execute(*spKaggleMsg, *spImdbMsg);
    } catch (...) {
        // failed due to exception
        return -1;
    }
    //if you want to see results uncomment code below
    //std::string IMDBReviewerRating = (*spImdbMsg).getIMDBReviewerRatingString();
    //std::cout << "IMDB Review" << std::endl;
    //std::cout << "    " << IMDBReviewerRating << std::endl;
    //std::basic_ostream << *spImdbMsg << "\n";    

    return 0;
}

//this function returns the imdb movie review
const char* return_imdb_review(void *msg) {
    PosNegReviews::IMDBMovieReview *the_imdbMsg = (PosNegReviews::IMDBMovieReview *) msg;
    std::string myc_string = (*the_imdbMsg).getIMDBReviewerRatingString();
    const char* theIMDBReviewerRating = myc_string.c_str();
    //if you want to see results uncomment code below
    //std::cout << "IMDB Review" << std::endl;
    //std::cout << "    " << theIMDBReviewerRating << std::endl;
    return theIMDBReviewerRating;
}

//free kaggle message after use
void free_kaggle_msg(void *msg) {
    OneToFiveReviews::KaggleMovieReview *kaggleMsg =
        (OneToFiveReviews::KaggleMovieReview *) msg;
    delete kaggleMsg;
}

//free imdb message after use
void free_imdb_msg(void *msg) {
    PosNegReviews::IMDBMovieReview *imdbMsg =
        (PosNegReviews::IMDBMovieReview *) msg;
    delete imdbMsg;
}

}