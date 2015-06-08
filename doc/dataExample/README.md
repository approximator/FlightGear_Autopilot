# Example FlightGear data

## How to use

```bash
pv dataExample/outExampleApp1 -L 4k | nc -u localhost 5555
```

## Run parameter for first FlightGear instance (callsing: App1)

```bash
/usr/games/fgfs			\
  --airport=KSFO		\
  --runway=10L			\
  --aircraft=c172p		\
  --console				\
  --bpp=32				\
  --disable-random-objects		\
  --disable-ai-models			\
  --disable-ai-traffic			\
  --disable-real-weather-fetch	\
  --geometry=1366x768			\
  --timeofday=morning			\
  --disable-terrasync			\
  --disable-clouds3d			\
  --disable-horizon-effect		\
  --disable-enhanced-lighting	\
  --callsign=App1				\
  --multiplay=out,10,mpserver02.flightgear.org,5000 \
  --multiplay=in,10,,5000	\
  --httpd=5050				\
  --generic=file,out,40,/tmp/outExampleApp1,FgaOut
```

## Run parameter for second FlightGear instance (callsing: App2)

```bash
/usr/games/fgfs 				\
  --airport=KSFO				\
  --runway=10L					\
  --aircraft=c172p				\
  --console						\
  --bpp=32						\
  --disable-random-objects		\
  --disable-ai-models			\
  --disable-ai-traffic			\
  --disable-real-weather-fetch	\
  --geometry=1366x768			\
  --timeofday=morning			\
  --disable-terrasync			\
  --disable-clouds3d			\
  --disable-horizon-effect		\
  --disable-enhanced-lighting	\
  --callsign=App2				\
  --multiplay=out,10,mpserver02.flightgear.org,5000 \
  --multiplay=in,10,,5001		\
  --httpd=5051					\
  --generic=file,out,40,/tmp/outExampleApp2,FgaOut
```
