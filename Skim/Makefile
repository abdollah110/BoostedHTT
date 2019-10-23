CPPFLAGS=`root-config --cflags` -I/usr/local/root/include
LDFLAGS=`root-config --libs` -lMinuit
all: Skimerloc SkimerBoost_mt  SkimerBoost_et SkimerBoost_mm SkimerBoost_EffMeasurement
Skimerloc: Skimer_local.cc		
	g++ $(CPPFLAGS) $(LDFLAGS) -o $@ $^
SkimerBoost_mt: SkimerBoost_mt.cc
	g++ $(CPPFLAGS) $(LDFLAGS) -o $@ $^
SkimerBoost_et: SkimerBoost_et.cc
	g++ $(CPPFLAGS) $(LDFLAGS) -o $@ $^
SkimerBoost_mm: SkimerBoost_mm.cc
	g++ $(CPPFLAGS) $(LDFLAGS) -o $@ $^
SkimerBoost_EffMeasurement: SkimerBoost_EffMeasurement.cc
	g++ $(CPPFLAGS) $(LDFLAGS) -o $@ $^

