# MQTT Midnight Sun

This project is an Arduino-based ESP2866 hack. It is intended to connect a
JRTronic 100W PWM LED controller to an ESP2866, and expose brightness as an
MQTT endpoint. If successful, I'll be modifying it to support more than one
JRTronic driver, with the goal of fading between 5600k "daylight" and 3200k
"tungsten" color balance.

Big picture, I'm trying to make a big bright light source so my brain doesn't
get so grumpy that I'm biking home from work in the dark every night this
winter. It's not a SAD lamp, because it isn't a medical device of any sort (and I'm not 100% convinced of the efficacy of that stuff anyhow). It's really more of a Melancholy Lamp.

I'm calling it the Midnight Sun after those spotlights on police and SAR helicopters. It's really bright.

## Build Requirements
* [Arduino ESP2866 core](https://github.com/esp8266/Arduino)
* [Arduino PubSub Client](https://github.com/knolleary/pubsubclient/) (Can be
installed via Library Manager).

## Hardware Requirements
* PWM-dimmable LED driver. I used  the [JRTronic UV363-100-PWM](http://ac-rc.net/catalog/product_info.php?manufacturers_id=22&products_id=241) because it was everything I needed in a sealed box. You can also roll your own.
* Big bright LED COB module. I used a [Yuji BC-series 400H 100W](http://store.yujiintl.com/products/bc-series-cob-400hs?variant=488243517). The key features were daylight color temperature and high color rendition index (CRI).
* Heatsink for LED COB module. I used [this Amazon module](https://www.amazon.com/gp/product/B01D1LD682), which includes a 120 degree lens and LED holder.

## Caveats

The JRTronic dimmer takes mains AC in. *THIS STUFF CAN HURT YOU IF YOU ARE NOT CAREFUL!* Please take appropriate precautions when working with mains AC. I used a Power Entry Module (PEM) with an integral fuse holder and LC filter, and insulated connectors everywhere. I also made sure to ground the metal case of the JRTronic box to the ground line of the PEM.  If you are at all unclear on this, please consult someone with more experience. Please don't just dive into this if you've never worked with AC before -- it's possible to do safely but Advice From Random Internet Guy alone is probably insufficient to do so.

The big 100W COB LED throws a lot of heat. I attached mine to a heatsink with a 12v fan (heatsink thermal monitoring and fan speed control code coming soon!)
