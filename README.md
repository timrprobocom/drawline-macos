# wxWidgets DrawLines issue on MacOS

This sample is extracted from a much larger program that draws telemetry
data.  I need to plot 6,000 lines several times a second.  On Windows and 
on Linux, the calls take 100ms.  On MacOS, these calls take MANY seconds.  
In fact, on my MacBook Pro 15 with a 2.2 GHz i7, I had to cut this test 
back to 600 lines to get any timing at all:

| wxWidgets version | OS | CPU | #Lines | Cycles |
|---|---|---|---|---|
| 3.1.3 | Windows | 3.4GHz i7 | 6000 | 180 million |
| 3.0.4 | Linux | 2.7GHz i7 | 6000 |35 million |
| 3.0.4 | MacOS | 2.2GHz i7 | 600 | 5 BILLION (2.5 seconds) |

This seems suboptimal.  Note that wxClientDC and wxPaintDC behave 
identically.

## Short Followup

If I do the drawing as 60 calls with 100 in each call, I can draw all
6,000 lines on the Mac in 100M cycles.  If I do them as 30 calls with
200 in each, it takes 30 times as long.  And, a noted above, one call of
600 lines takes 50 times as long.  The time is exponential.
