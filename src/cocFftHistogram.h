/**
 *
 *      ┌─┐╔═╗┌┬┐┌─┐
 *      │  ║ ║ ││├┤
 *      └─┘╚═╝─┴┘└─┘
 *   ┌─┐┌─┐╔╗╔┬  ┬┌─┐┌─┐
 *   │  ├─┤║║║└┐┌┘├─┤└─┐
 *   └─┘┴ ┴╝╚╝ └┘ ┴ ┴└─┘
 *
 * Copyright (c) 2016 Code on Canvas Pty Ltd, http://CodeOnCanvas.cc
 *
 * This software is distributed under the MIT license
 * https://tldrlegal.com/license/mit-license
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code
 *
 **/

#pragma once

#include "cinder/audio/audio.h"

namespace coc {

struct FftData {
	int size;
	std::vector<float> data;
	std::vector<float> dataNorm;
	std::vector<float> dataMax;
	std::vector<float> dataPeak;
	std::vector<int> dataCut;
	float maxDecay;
	float peakValue;
	float peakDecay;
	float peakAverage;
	float cutThreshold;
	float linearEQIntercept;
	float linearEQSlope;
};


class FftHistogram {

public:

	void setup( std::string _label, int _fftSize );

	void connectNode( ci::audio::GainNodeRef _ref );
	void connectNode( ci::audio::BufferPlayerNodeRef _ref );

	void update();
	void updateUI();

	// GETTERS / SETTERS

	void setThreshold( float value );
	float getThreshold();

	float getAveragePeak();
	void setPeakDecay( float value );
	float getPeakDecay();

	void setMaxDecay( float value );
	float getMaxDecay();

	int getSize();

	const std::vector<float> &getFftRawData();
	const std::vector<float> &getFftNormData();
	const std::vector<float> &getFftPeakData();
	const std::vector<int> &getGlitchData();

	const std::vector<float> &getFftRawDataGrouped( int num );

	bool setUseNormVals( bool _use );

	float getAverageVolume();
	float getMaxVolume();

	void  setIsMirrored( bool _b ) { isMirrored = _b; }

	// FOR GUI:

	float * getMaxDecayRef() { return &fftData.maxDecay; };
	float * getPeakDecayRef() { return &fftData.peakDecay; };
	float * getThresholdRef() { return &fftData.cutThreshold; };
	bool * getUseNormValsRef() { return &useNormVals; }


private:

	void mirrorAudioData( FftData & audioData);

	ci::audio::MonitorNodeRef monitorNode;
	ci::audio::MonitorSpectralNodeRef monitorSpectralNode;
	std::vector<float> magSpectrum;
	std::string label;

	FftData fftData;
	bool useNormVals = false;
	bool isMirrored = false;

	std::vector<float> dataGrouped;

};//class FftHistogram


}//namespace coc
