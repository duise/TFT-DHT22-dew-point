# TFT-DHT22-dew-point
arduino mega with dht22 for temperature and humidity and 2,6" TFT shield. Calculate dew point.
master has no dew point. try to implement code for calculation of dp based on https://www.wetterochs.de/wetter/feuchte.html

Bezeichnungen:
r = relative Luftfeuchte
T = Temperatur in °C
TK = Temperatur in Kelvin (TK = T + 273.15)
TD = Taupunkttemperatur in °C
DD = Dampfdruck in hPa
SDD = Sättigungsdampfdruck in hPa

Parameter:
a = 7.5, b = 237.3 für T >= 0
a = 7.6, b = 240.7 für T < 0 über Wasser (Taupunkt)
a = 9.5, b = 265.5 für T < 0 über Eis (Frostpunkt)

R* = 8314.3 J/(kmol*K) (universelle Gaskonstante)
mw = 18.016 kg/kmol (Molekulargewicht des Wasserdampfes)
AF = absolute Feuchte in g Wasserdampf pro m3 Luft

Formeln:

    SDD(T) = 6.1078 * 10^((a*T)/(b+T))
    DD(r,T) = r/100 * SDD(T)
    r(T,TD) = 100 * SDD(TD) / SDD(T)
    TD(r,T) = b*v/(a-v) mit v(r,T) = log10(DD(r,T)/6.1078)
    AF(r,TK) = 10^5 * mw/R* * DD(r,T)/TK; AF(TD,TK) = 10^5 * mw/R* * SDD(TD)/TK
