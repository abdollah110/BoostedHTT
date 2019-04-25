CPPFLAGS=`root-config --cflags` -I/usr/local/root/include
LDFLAGS=`root-config --libs` -lMinuit
all: Skimerloc SkimerBoost
Skimerloc: Skimer_local.cc		
	g++ $(CPPFLAGS) $(LDFLAGS) -o $@ $^
SkimerBoost: SkimerBoost.cc
	g++ $(CPPFLAGS) $(LDFLAGS) -o $@ $^
