module MovieTransforms.KaggleToIMDBTransform

import IMDBReviews::v2.PosNegReviews as imdb
import KaggleReviews::v3.OneToFiveReviews as kaggle

transform IMDBfromKaggle(kagglereview : kaggle.KaggleMovieReview) -> imdb.IMDBMovieReview {
    imdb.IMDBMovieReview {
        IMDBReviewerRating = if (kagglereview.KaggleReviewerRating == kaggle.KReviewRating.One) {
            imdb.ReviewRating.Negative;
        } else if (kagglereview.KaggleReviewerRating == kaggle.KReviewRating.Two) {
           imdb.ReviewRating.Negative;
        } else if (kagglereview.KaggleReviewerRating == kaggle.KReviewRating.Three) {
           imdb.ReviewRating.Positive;
        } else if (kagglereview.KaggleReviewerRating == kaggle.KReviewRating.Four) {
            imdb.ReviewRating.Positive;
        } else {
            imdb.ReviewRating.Positive;
        };
    };
}