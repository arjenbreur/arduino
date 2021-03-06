#include "SmoothAnalogInput.h"

SmoothAnalogInput::SmoothAnalogInput() {
    _pin = -1;
	_sampleSize = 1;
	_maxSampleSize = SMOOTH_ANALOG_INPUT_SIZE;
    _index = -1;
    _mapMax = 1024;
    _mapMin = 0;
    _res = 1;
}

// DEPRECATED, use setup() instead
void SmoothAnalogInput::attach(int pin) {
	setup(pin, _maxSampleSize);
}

void SmoothAnalogInput::setup(byte pin, int sampleSize){
	_pin = pin;
	_sampleSize = (sampleSize<=_maxSampleSize)?sampleSize:_maxSampleSize;
    _index = 0;
    int start = analogRead(pin);
    for(int i = 0; i < _sampleSize; i++) {
        _samples[i] = start;
    }
}

void SmoothAnalogInput::scale(int min, int max) {
    if (max <= min) {
        return;
    }

    _mapMin = min;
    _mapMax = max;

    _res = 1024 / (max - min) * 2;
}

int SmoothAnalogInput::raw() {
    if (_pin == -1) {
        return -1;
    }

    int value = analogRead(_pin);
    int last = _samples[_index];
    if (abs(value - last) <= _res) {
        value = last;
    }

    _index = (_index + 1) % _sampleSize;
    _samples[_index] = value;

    return value;
}

int SmoothAnalogInput::read() {
    raw();

    int total = 0;
    for(int i = 0; i < _sampleSize; i++) {
        total += _samples[i];
    }

    int current = total / _sampleSize;
    return map(current, 0, 1024, _mapMin, _mapMax);
}
