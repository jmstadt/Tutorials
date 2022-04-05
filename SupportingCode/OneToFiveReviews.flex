module KaggleReviews.OneToFiveReviews

enum KReviewRating int32 {
  One = 1;
  Two = 2;
  Three = 3;
  Four = 4;
  Five = 5;
}

message struct KaggleMovieReview {
  KaggleReviewerRating: KReviewRating;
}