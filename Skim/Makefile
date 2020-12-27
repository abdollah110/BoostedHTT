CPPFLAGS=`root-config --cflags` -I/usr/local/root/include
LDFLAGS=`root-config --libs` -lMinuit
all: SkimerBoost_mt  SkimerBoost_et SkimerBoost_mm SkimerBoost_EffMeasurement SkimerBoost_tt SkimerBoost_em SkimerBoost_mmtt
SkimerBoost_mt: SkimerBoost_mt.cc
	g++ $(CPPFLAGS) $(LDFLAGS) -o $@ $^
SkimerBoost_et: SkimerBoost_et.cc
	g++ $(CPPFLAGS) $(LDFLAGS) -o $@ $^
SkimerBoost_mm: SkimerBoost_mm.cc
	g++ $(CPPFLAGS) $(LDFLAGS) -o $@ $^
SkimerBoost_EffMeasurement: SkimerBoost_EffMeasurement.cc
	g++ $(CPPFLAGS) $(LDFLAGS) -o $@ $^
SkimerBoost_tt: SkimerBoost_tt.cc
	g++ $(CPPFLAGS) $(LDFLAGS) -o $@ $^
SkimerBoost_em: SkimerBoost_em.cc
	g++ $(CPPFLAGS) $(LDFLAGS) -o $@ $^
SkimerBoost_mmtt: SkimerBoost_mmtt.cc
	g++ $(CPPFLAGS) $(LDFLAGS) -o $@ $^

