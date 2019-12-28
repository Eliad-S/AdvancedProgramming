//
// Created by eliadsellem on 12/10/19.
//


#include "InterpreterFlight.h"

InterpreterFlight *InterpreterFlight::instance = 0;

unordered_map<string, Command *> &InterpreterFlight::get_CommandMap() {
    return this->commandMap;
}

unordered_map<string, Obj *> &InterpreterFlight::get_STSimulatorMap() {
    return this->STSimulatorMap;
}

unordered_map<string, Obj *> &InterpreterFlight::get_STObjMap() {
    return this->STObjMap;
}

vector<string> &InterpreterFlight::get_Array() {
    return this->array;
}

void InterpreterFlight::setTokens(vector<string> &tokens) {
    this->array = tokens;
}

void InterpreterFlight::parser() {

    unsigned int index = 0;
    while (index < array.size()) {
        unordered_map<string, Command *>::iterator itCommand;
        itCommand = commandMap.find(array[index]);
        if (itCommand != commandMap.end()) {
            Command *c = commandMap.find(array[index])->second;
            index += c->execute(index);
        }
    }

    this->keepOpenServerThread = false;
    this->keepOpenClientThread = false;
    serverThread.join();
    clientThread.join();

}

void InterpreterFlight::setCommandMap(unordered_map<string, Command *> &map) {
    map["openDataServer"] = new OpenDataCommand();
    map["connectControlClient"] = new OpenControlCommand();
    map["var"] = new VarCommand();
    map["Print"] = new PrintCommand();
    map["Sleep"] = new SleepCommand();
    map["obj"] = new ObjCommand();
    map["while"] = new WhileCommand();
    map["if"] = new IfCommand();
}

void InterpreterFlight::setSTSimulatorMap(unordered_map<string, Obj *> &map) {
    Obj *airspeed_indicator_indicated_speed_kt = new Obj("/instrumentation/airspeed-indicator/indicated-speed-kt");
    map["airspeed_indicator_indicated_speed_kt"] = airspeed_indicator_indicated_speed_kt;
    Obj *time_warp = new Obj("/sim/time/warp");
    map["time_warp"] = time_warp;
    Obj *switches_magnetos = new Obj("/controls/switches/magnetos");
    map["switches_magnetos"] = switches_magnetos;
    Obj *heading_indicator_offset_deg = new Obj("/instrumentation/heading-indicator/offset-deg");
    map["heading_indicator_offset_deg"] = heading_indicator_offset_deg;
    Obj *altimeter_indicated_altitude_ft = new Obj("/instrumentation/altimeter/indicated-altitude-ft");
    map["altimeter_indicated_altitude_ft"] = altimeter_indicated_altitude_ft;
    Obj *altimeter_pressure_alt_ft = new Obj("/instrumentation/altimeter/pressure-alt-ft");
    map["altimeter_pressure_alt_ft"] = altimeter_pressure_alt_ft;
    Obj *attitude_indicator_indicated_pitch_deg = new Obj("/instrumentation/attitude-indicator/indicated-pitch-deg");
    map["attitude_indicator_indicated_pitch_deg"] = attitude_indicator_indicated_pitch_deg;
    Obj *attitude_indicator_indicated_rolL_deg = new Obj("/instrumentation/attitude-indicator/indicated-roll-deg");
    map["attitude_indicator_indicated_rolL_deg"] = attitude_indicator_indicated_rolL_deg;
    Obj *attitude_indicator_internal_pitch_deg = new Obj("/instrumentation/attitude-indicator/internal-pitch-deg");
    map["attitude_indicator_internal_pitch_deg"] = attitude_indicator_internal_pitch_deg;
    Obj *attitude_indicator_internal_roll_deg = new Obj("/instrumentation/attitude-indicator/internal-roll-deg");
    map["attitude_indicator_internal_roll_deg"] = attitude_indicator_internal_roll_deg;
    Obj *encoder_indicated_altitude_ft = new Obj("/instrumentation/encoder/indicated-altitude-ft");
    map["encoder_indicated_altitude_ft"] = encoder_indicated_altitude_ft;
    Obj *encoder_pressure_alt_ft = new Obj("/instrumentation/encoder/pressure-alt-ft");
    map["encoder_pressure_alt_ft"] = encoder_pressure_alt_ft;
    Obj *gps_indicated_altitude_ft = new Obj("/instrumentation/gps/indicated-altitude-ft");
    map["gps_indicated_altitude_ft"] = gps_indicated_altitude_ft;
    Obj *gps_indicated_ground_speed_kt = new Obj("/instrumentation/gps/indicated-ground-speed-kt");
    map["gps_indicated_ground_speed_kt"] = gps_indicated_ground_speed_kt;
    Obj *gps_indicated_vertical_speed = new Obj("/instrumentation/gps/indicated-vertical-speed");
    map["gps_indicated_vertical_speed"] = gps_indicated_vertical_speed;
    Obj *indicated_heading_deg = new Obj("/instrumentation/heading-indicator/indicated-heading-deg");
    map["indicated_heading_deg"] = indicated_heading_deg;
    Obj *magnetic_compass_indicated_heading_deg = new Obj("/instrumentation/magnetic-compass/indicated-heading-deg");
    map["magnetic_compass_indicated_heading_deg"] = magnetic_compass_indicated_heading_deg;
    Obj *slip_skid_ball_indicated_slip_skid = new Obj("/instrumentation/slip-skid-ball/indicated-slip-skid");
    map["slip_skid_ball_indicated_slip_skid"] = slip_skid_ball_indicated_slip_skid;
    Obj *turn_indicator_indicated_turn_rate = new Obj("/instrumentation/turn-indicator/indicated-turn-rate");
    map["turn_indicator_indicated_turn_rate"] = turn_indicator_indicated_turn_rate;
    Obj *vertical_speed_indicator_indicated_speed_fpm =
            new Obj("/instrumentation/vertical-speed-indicator/indicated-speed-fpm");
    map["vertical_speed_indicator_indicated_speed_fpm"] = vertical_speed_indicator_indicated_speed_fpm;
    Obj *flight_aileron = new Obj("/controls/flight/aileron");
    map["flight_aileron"] = flight_aileron;
    Obj *flight_elevator = new Obj("/controls/flight/elevator");
    map["flight_elevator"] = flight_elevator;
    Obj *flight_rudder = new Obj("/controls/flight/rudder");
    map["flight_rudder"] = flight_rudder;
    Obj *flight_flaps = new Obj("/controls/flight/flaps");
    map["flight_flaps"] = flight_flaps;
    Obj *engine_throttle = new Obj("/controls/engines/engine/throttle");
    map["engine_throttle"] = engine_throttle;
    Obj *current_engine_throttle = new Obj("/controls/engines/current-engine/throttle");
    map["current_engine_throttle"] = current_engine_throttle;
    Obj *switches_master_avionics = new Obj("/controls/switches/master-avionics");
    map["switches_master_avionics"] = switches_master_avionics;
    Obj *switches_starter = new Obj("/controls/switches/starter");
    map["switches_starter"] = switches_starter;
    Obj *active_engine_auto_start = new Obj("/engines/active-engine/auto-start");
    map["active_engine_auto_start"] = active_engine_auto_start;
    Obj *flight_speedbrake = new Obj("/controls/flight/speedbrake");
    map["flight_speedbrake"] = flight_speedbrake;
    Obj *c172p_brake_parking = new Obj("/sim/model/c172p/brake-parking");
    map["c172p_brake_parking"] = c172p_brake_parking;
    Obj *engine_primer = new Obj("/controls/engines/engine/primer");
    map["engine_primer"] = engine_primer;
    Obj *current_engine_mixture = new Obj("/controls/engines/current-engine/mixture");
    map["current_engine_mixture"] = current_engine_mixture;
    Obj *switches_master_bat = new Obj("/controls/switches/master-bat");
    map["switches_master_bat"] = switches_master_bat;
    Obj *switches_master_alt = new Obj("/controls/switches/master-alt");
    map["switches_master_alt"] = switches_master_alt;
    Obj *engine_rpm = new Obj("/engines/engine/rpm");
    map["engine_rpm"] = engine_rpm;
}

void InterpreterFlight::setSimArray() {
    sims[0] = "/instrumentation/airspeed-indicator/indicated-speed-kt";
    sims[1] = "/sim/time/warp";
    sims[2] = "/controls/switches/magnetos";
    sims[3] = "/instrumentation/heading-indicator/offset-deg";
    sims[4] = "/instrumentation/altimeter/indicated-altitude-ft";
    sims[5] = "/instrumentation/altimeter/pressure-alt-ft";
    sims[6] = "/instrumentation/attitude-indicator/indicated-pitch-deg";
    sims[7] = "/instrumentation/attitude-indicator/indicated-roll-deg";
    sims[8] = "/instrumentation/attitude-indicator/internal-pitch-deg";
    sims[9] = "/instrumentation/attitude-indicator/internal-roll-deg";
    sims[10] = "/instrumentation/encoder/indicated-altitude-ft";
    sims[11] = "/instrumentation/encoder/pressure-alt-ft";
    sims[12] = "/instrumentation/gps/indicated-altitude-ft";
    sims[13] = "/instrumentation/gps/indicated-ground-speed-kt";
    sims[14] = "/instrumentation/gps/indicated-vertical-speed";
    sims[15] = "/instrumentation/heading-indicator/indicated-heading-deg";
    sims[16] = "/instrumentation/magnetic-compass/indicated-heading-deg";
    sims[17] = "/instrumentation/slip-skid-ball/indicated-slip-skid";
    sims[18] = "/instrumentation/turn-indicator/indicated-turn-rate";
    sims[19] = "/instrumentation/vertical-speed-indicator/indicated-speed-fpm";
    sims[20] = "/controls/flight/aileron";
    sims[21] = "/controls/flight/elevator";
    sims[22] = "/controls/flight/rudder";
    sims[23] = "/controls/flight/flaps";
    sims[24] = "/controls/engines/engine/throttle";
    sims[25] = "/controls/engines/current-engine/throttle";
    sims[26] = "/controls/switches/master-avionics";
    sims[27] = "/controls/switches/starter";
    sims[28] = "/engines/active-engine/auto-start";
    sims[29] = "/controls/flight/speedbrake";
    sims[30] = "/sim/model/c172p/brake-parking";
    sims[31] = "/controls/engines/engine/primer";
    sims[32] = "/controls/engines/current-engine/mixture";
    sims[33] = "/controls/switches/master-bat";
    sims[34] = "/controls/switches/master-alt";
    sims[35] = "/engines/engine/rpm";
}

bool InterpreterFlight::getKeepOpenServerThread() {
    return this->keepOpenServerThread;
}

bool InterpreterFlight::getKeepOpenClientThread() {
    return this->keepOpenClientThread;
}

void InterpreterFlight::setSTObjMap(string varName, Obj *obj) {
    InterpreterFlight::getInstance()->mutex_.lock();
    STObjMap[varName] = obj;
    InterpreterFlight::getInstance()->mutex_.unlock();
}

string InterpreterFlight::getIndexOfArray(int index) {
    return sims[index];
}

Obj *InterpreterFlight::get_STSimulatorObjBySim(string sim) {
    unordered_map<string, Obj *>::iterator it = STSimulatorMap.begin();
    for (; it != STSimulatorMap.end(); it++) {
        if (it->second->getSim() == sim) {
            return it->second;
        }
    }
    return nullptr;
}

void InterpreterFlight::pushQueue(Obj *obj) {
    InterpreterFlight::getInstance()->mutex_2.lock();
    this->objToUpdate.push(obj);
    InterpreterFlight::getInstance()->mutex_2.unlock();

}

void InterpreterFlight::popQueue() {
    InterpreterFlight::getInstance()->mutex_2.lock();
    this->objToUpdate.pop();
    InterpreterFlight::getInstance()->mutex_2.unlock();

}

queue<Obj *> &InterpreterFlight::getQueue() {
    return this->objToUpdate;
}

InterpreterFlight::~InterpreterFlight() {
    for (auto it1 : STSimulatorMap) {
        if (STObjMap.find(it1.second->getName()) != STObjMap.end()) {
            STObjMap.erase(it1.second->getName());
        }
        delete it1.second;
    }
    for (auto it2 : STObjMap) {
        delete it2.second;
    }

    for (auto it3 : commandMap) {
        delete it3.second;
    }
}
