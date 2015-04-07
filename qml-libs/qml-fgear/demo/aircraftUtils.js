.pragma library
var __aircraftsCounter = 0;
var aircraft_models = [ "b1900d", "beech99", "f22-raptor", "fgJet", "il-96-400T" ]

function createVehicleInfo(_model,_image_type){
    var info = {}
    info.model = _model;
    info.image = "flight_pic/" + _model + "." +_image_type;
    return info;
}

function newAircraft() {

    // Creating aircraft object like in FgAircraft.h
    var that = {
        callsign: __createCallsign(),
        index: __createIndex(),
        params: newParams(),
        controls: newControls(),
        update: function () {
            this.controls.controlStep();
            this.params.flyStep();
        }
    };
    that.vehicleInfo = createVehicleInfo(aircraft_models[that.index], "png");

    return that;
}

function __createCallsign() {
    return Date().toString();
}

function __createIndex() {
    return (__aircraftsCounter+=1);
}

function newParams() {
    var that = {
        pitch: 0,          //deg
        roll: 0,             //deg
        yaw: 0,           //deg
        longitude: 0,   //deg
        latitude: 0,      //deg
        altitude: 0,      //ft
        heading: 0,     //deg
        flyStep: __fillRandom
    };

    return that;
}

function newControls() {
    var that = {
        ailerons: 0,
        elevator: 0,
        rudder: 0,
        controlStep: __fillRandom
    }
    return that;
}

function __getRandomArbitary(min, max) {
    return (Math.random() * (max - min) + min);
}

/*
  This function fills all fields of the object with random values.
  */
function __fillRandom() {
    var obj = this;
    for (var prop in obj) {
        if (obj.hasOwnProperty(prop) && (typeof obj[prop] != "function")) {
            obj[prop] = __getRandomArbitary(0,10);
            console.log(prop, obj[prop]);
        }
    }
}
