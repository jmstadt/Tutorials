module IMDBReviews.PosNegReviews

enum ReviewRating int32 {
  Negative = 0;
  Positive = 1;
}

message struct IMDBMovieReview {
  IMDBReviewerRating: ReviewRating;
}