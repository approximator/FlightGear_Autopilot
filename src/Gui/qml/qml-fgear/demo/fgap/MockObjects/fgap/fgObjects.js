/*
* Copyright © 2017 Andrii Shelest. All rights reserved.
* Author: Andrii Shelest (ext-andrii.shelest@here.com)
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

.pragma library

var Aircraft = (function () {
    function Aircraft (call_sign)
    {
        console.log("[testFgapObjects] Creating aircraft object ", call_sign);

        this.callsign = (call_sign !== "")
             ? call_sign
             : this.__createCallsign();
        this.connected = false;
    }

    Aircraft.prototype.__createCallsign = function () {
        return Date().toString();
    };

    Aircraft.prototype.__randomArbitary = function (min, max) {
        return (Math.random() * (max - min) + min);
    };

    return Aircraft;
})();

/*var aircraft_models = [ "b1900d", "beech99", "f22-raptor", "fgJet", "il-96-400T" ]

function createVehicleInfo(_model,_image_type){
    var info = {}
    info.model = _model;
    info.image = "flight_pic/" + _model + "." +_image_type;
    return info;
}

function newAircraft(_callsign) {

    // Creating aircraft object like in FgAircraft.h
    var that = {
        callsign: _callsign !== "" ? _callsign : __createCallsign(),
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

*/
