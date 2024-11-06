//API-Constants: defines, enumerations, const variables


//Pump type table: Pump type is calculated by piston size, number of pumps, and the stroke length.
//
//                                                     Displacement (mL)             Displacement (mL)             Displacement (mL)
//                                                     Stroke=0.125 inch             Stroke=0.250 inch             Stroke=0.500 inch
//
//Pump Type                                         1L         1S       1H         2L        2S       2H         3L       3S        3H
//
//Piston Size                                      D=.093    D=.125    D=.25     D=.093    D=.125    D=.25     D=.093    D=.125    D=.25
//
//Precise Displacement Volume (Floating Point)    0.013914  0.025137  0.10055    0.027829  0.050275  0.2011    0.055685  0.10055  0.402199
//Displacement Volume for Firmware (Rounded
//decimal for Display and Integer Calculations)     0.014    0.025     0.10       0.028     0.05      0.20       0.056     0.10     0.40
//
//Minimum Flow Rates (milliliters per minute)      0,002     0,003     0,01       0,003     0,01      0,02        0,01     0,01     0,04
//Maximum Flow Rates (milliliters per minute)       2,5        5        20          5        10        40          10       20       80
//
//Max Pressure Stainless (M) or Hastelloy-C (MH)     6000    6000      3000        6000     6000      1500        3000     1500     750
//in PSI
//Max Pressure PEEK (I) PSI                          4000    4000      3000        4000     4000      1500        3000     1500     750


