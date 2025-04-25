% DEFINE REYNOLD'S NUMBER FOR THIS GEOMETRY

% define constants, Rho is the density of the fluid (particulate included 
% not sure how to calculate, just using a fixed value based on distilled
% water for now


% u is the linear speed. will define based on an omega, which comes from
% steps per second, and microsteps per revolution. 

% L is the characteristic linear dimension. We set L = R_o - R_i by
% convention, but other selections are valid. We care about the shape of
% the phase space more than the specific values.

% mu is the dynamic viscosity. 


% Define the geometry of the system by inputting the inner and outer Radii

% Inner Radius = 137.30 mm = 0.1373 meters
R_i = 0.1373;

% Outer Radius = 155.575 mm = 0.155575 meters
% NOTE: this is the inner measurement of the outer cylinder -- the surface
% actually contacting the fluid, and not the outer radius that is exposed
% to free space.
R_o = 0.155575;


% Dynamic Viscosity of water = 0.000878 N*s/m2 at 78 deg Fahrenheit.

% sourced from https://www.engineeringtoolbox.com/water-dynamic-kinematic-viscosity-d_596.html

mu = 0.000878;


% 1000 kg / m^3
rho = 1000;

% L = Outer Radius - Inner Radius
L = R_o - R_i;

% speed here is defined by angular speed.
% to set RPM, we take (pulses per second&* revs/pulse aka. (inverse of table pulse/rev)/2)*60
% u = RPM *2*pi/60


% select an RPM
RPM = 0.021;

u = RPM * 2*pi/60;

Re = (rho * u * L) / mu ;



% steps are 1.8 degrees. steps per second only refers to the angular range
% we cross. Microsteps divide up that step partition. Our motor does 200
% steps per rev. So every multiple of 200 for the pulses per rev defines a
% different step ratio

% Microstep Setting | Pulses per Revolution
% 1 (Full step) | 200
% 2 (Half step) | 400
% 4 | 800
% 8 | 1600
% 16 | 3200
% 32 | 6400
% 64 | 12800

