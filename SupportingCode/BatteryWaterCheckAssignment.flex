module BatteryWaterCheckAssignment::v2.BatteryWaterCheck

//version 2

enum CheckStatus int32 {
  Ian = 1;
  Mark = 2;
  NotNeeded = 3;
}

message struct CheckStatusMessage {
  CheckAssignment: CheckStatus;
}