module BWCAfromIMPR.BWCAfromIMPRgivenDSLC

import BatteryWaterCheckAssignment::v2.BatteryWaterCheck as bwca
import IanMarkPositionReport::v1.IanMarkPosition as impr

function acos(x : float64) -> float64 {
    2.0*atan2(sqrt(1.0-x*x)/(1.0+x),1.0);
}

struct DaysSinceLastCheck { 
    dslc: int32;  
}

newtype NewC { 
    value: DaysSinceLastCheck; 
}

transform BWCAfromIMPR(posReports: impr.IanMarkPositionMessage) -> bwca.CheckStatusMessage given(?c: NewC) {
    let homeLat = 32.81974;
    let homeLong = -79.87904;
    let ianLatRad = posReports.ianLat / (180.0/3.14159); 
    let ianLongRad = posReports.ianLong / (180.0/3.14159);
    let markLatRad = posReports.markLat / (180.0/3.14159); 
    let markLongRad = posReports.markLong / (180.0/3.14159);
    let homeLatRad = homeLat / (180.0/3.14159);
    let homeLongRad = homeLong / (180.0/3.14159);
    let acos_prep_ian = (sin(homeLatRad) * sin(ianLatRad)) + cos(homeLatRad) * cos(ianLatRad) * cos(ianLongRad - homeLongRad);
    let acos_prep_mark = (sin(homeLatRad) * sin(markLatRad)) + cos(homeLatRad) * cos(markLatRad) * cos(markLongRad - homeLongRad);
    let ianToHome = 3963.0*acos(acos_prep_ian);
    let markToHome = 3963.0*acos(acos_prep_mark);
    let days : int32 = ?c.value.dslc;
    bwca.CheckStatusMessage {
        CheckAssignment = if (days < 31) {
            bwca.CheckStatus.NotNeeded;
        } else if (ianToHome < markToHome) {
            bwca.CheckStatus.Ian;
        } else {
            bwca.CheckStatus.Mark;
        };
    };
}

