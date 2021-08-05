CPPFLAGS=`root-config --cflags` -I/usr/local/root/include
LDFLAGS=`root-config --libs` -lMinuit
all: SkimerBoost_mt  SkimerBoost_et SkimerBoost_mm SkimerBoost_EffMeasurement SkimerBoost_tt SkimerBoost_em SkimerBoost_mmt SkimerBoost_tt_htmht SkimerBoost_mj_2016 SkimerBoost_mj_2017 SkimerBoost_mj_2018  SkimerBoost_tt_ht SkimerBoost_mFake SkimerBoost_mFake_deep SkimerBoost_me SkimerBoost_Differntial
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
SkimerBoost_mmt: SkimerBoost_mmt.cc
	g++ $(CPPFLAGS) $(LDFLAGS) -o $@ $^
SkimerBoost_tt_htmht: SkimerBoost_tt_htmht.cc
	g++ $(CPPFLAGS) $(LDFLAGS) -o $@ $^
SkimerBoost_tt_ht: SkimerBoost_tt_ht.cc
	g++ $(CPPFLAGS) $(LDFLAGS) -o $@ $^
SkimerBoost_mj_2016: SkimerBoost_mj_2016.cc
	g++ $(CPPFLAGS) $(LDFLAGS) -o $@ $^
SkimerBoost_mj_2017: SkimerBoost_mj_2017.cc
	g++ $(CPPFLAGS) $(LDFLAGS) -o $@ $^
SkimerBoost_mj_2018: SkimerBoost_mj_2018.cc
	g++ $(CPPFLAGS) $(LDFLAGS) -o $@ $^
SkimerBoost_mFake: SkimerBoost_mFake.cc
	g++ $(CPPFLAGS) $(LDFLAGS) -o $@ $^
SkimerBoost_mFake_deep: SkimerBoost_mFake_deep.cc
	g++ $(CPPFLAGS) $(LDFLAGS) -o $@ $^
SkimerBoost_me: SkimerBoost_me.cc
	g++ $(CPPFLAGS) $(LDFLAGS) -o $@ $^
SkimerBoost_Differntial: SkimerBoost_Differntial.cc
	g++ $(CPPFLAGS) $(LDFLAGS) -o $@ $^

