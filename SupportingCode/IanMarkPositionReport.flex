module IanMarkPositionReport::v1.IanMarkPosition

message struct IanMarkPositionMessage {
  ianLat: float64;
  ianLong: float64;
  markLat: float64;
  markLong: float64;
}