#pragma once
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <map>
#include <vector>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
using namespace std;

#define BUFFERSIZE 128
#define PERSON_DEBUG 0  // debug output switch

typedef struct PulseHead {
	uint32_t T0Head = 0xee1234ee; //0xee1234ee
	uint8_t SpectroId;
	uint8_t DetectorId;
	uint16_t Reserve1;
	uint8_t OperateMod;
	uint8_t FreqScaleMod;
	uint8_t DataVersion;
	uint8_t DataTypeId;
	uint8_t ModuleStatus12;
	uint8_t ModuleStatus34;
	uint8_t ModuleStatus56;
	uint8_t Reserve2;
	uint32_t ModuleSize1;
	uint32_t ModuleSize2;
	uint32_t ModuleSize3;
	uint32_t ModuleSize4;
	uint32_t ModuleSize5;
	uint32_t ModuleSize6;
	uint32_t T0Count;
	uint32_t PackSize;
	uint32_t SliceCount; //[0, SliceCount], number+1
	uint32_t Reserve3;
	uint32_t Reserve4;
	uint32_t Reserve5;
} PulseHead;

typedef struct SliceHead {
	uint32_t SliceId; //uint8_t(0xaa)+uint24_t(tDataId)
	uint32_t EventNumber; //ByteSize=EventNumber*8Bytes
} SliceHead;

typedef struct EventData {
	uint32_t TOF; //uint8_t(channel)+uint24_t(TOF)
	uint32_t Value; //uint8_t(channel)+uint12_t(Base)+uint12_t(Q)
} EventData;

typedef struct EventValue {
	//uint16_t base;
	//uint16_t Q;
	uint16_t bareQ;
	uint16_t channel;
	uint32_t tof; // new to vector algorithm
} EventValue;

typedef struct {
	float center;
	float charge;
	int tof;
	int t0num;
	int nstrip;
	int strip1st;
	float dQ;
	float cstrip[10];
	float qstrip[10];
	float bstrip[10];
	float tstrip[10];
	int match;
	int dT1;
	int dT2;
} Hit;

typedef struct Neutron {
	int t0num;
	float x;
	float y;
	float t;
	float tx;
	float ty;
	int nsx;
	int nsy;
	float qsum;
	float chargex;
	float chargey;
	float qx;
	float qy;
	float basex;
	float basey;
	float wl;
	float dqx;
	int dT;
	int matchx;
	int matchy;
} Neutron;
