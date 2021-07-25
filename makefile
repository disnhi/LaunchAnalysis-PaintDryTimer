OPTS = -Wall

all: time-code nasa pdt

time-code: TimeCodeTests.cpp TimeCode.cpp
	g++ -std=c++11 ${OPTS} -o time-code TimeCodeTests.cpp TimeCode.cpp

nasa: NASALaunchAnalysis.cpp TimeCode.cpp
	g++ -std=c++11 ${OPTS} -o nasa NASALaunchAnalysis.cpp TimeCode.cpp

pdt: PaintDryTimer.cpp TimeCode.cpp
	g++ -std=c++11 ${OPTS} -o pdt PaintDryTimer.cpp TimeCode.cpp
