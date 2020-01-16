% Elec 341 - 2019
% This script sets the model parameters

% Example: Specifying a Dynamics Block
% n = [1 2 3];
% d = [4 5 6];
% Transfer Function = (s^2 + 2s + 3) / (4s^2 + 5s + 6)

% =====
% FLAGS
% =====
% Set to 0 or 1

% Which values to over-write during development
CtlFlag = 1;                                    % Controller gains
AmpFlag = 1;                                    % Amplifier model
MotFlag = 1;                                    % Motor model
RobFlag = 1;                                    % Robot model
SenFlag = 1;                                    % Sensor model


% ========================
% PHYSICAL UNIT CONVERSION
% ========================
% Example: if you decide to work in (Kg), all masses must be represented
%          in (Kg) but the spec sheet may provide masses in (g)

% Electrical

% Mechanical


% ==============
% XFER FUNCTIONS
% ==============

% ------------------
% Controller Gains
if CtlFlag
 
% Q0
PID0 = [-0.00000482 -0.00000893 -0.00000293]; %KP KI KD
CtlSat0  = 4.5000;
FB0      = 0.9000;
%PID0 = [-0.035 -0.003 -0.0097]; %KP KI KD 31.57
%PID1 = [-0.025 -0.003 -0.0097]; %KP KI KD 31.63
%PID1 = [-0.020 -0.003 -0.0097]; %KP KI KD 33.43
%PID0 = [-0.017 -0.003 -0.0097]; %KP KI KD 34.94
%PID0 = [-0.015 -0.0038 -0.0097]; %KP KI KD 36.55
%PID1 = [-0.015 -0.003 -0.0097]; %KP KI KD 35.8
%PID0 = [0.00000482 0.00000893 0.00000293]; %KP KI KD values from part1
% Q1
PID1 = [-0.00000482 -0.00000893 -0.00000293]; %KP KI KD
CtlSat1  = 4.5000;
FB1      = 0.9000;

end; % CtlFlag
% ------------------


% ------------------
% Amplifier Dynamics
if AmpFlag

% Q0
Amp0n    = [-3.125 -92];
Amp0d    = [0.25 8];
AmpSat0  = 24;

% Q1
Amp1n    = [-3.125 -92];
Amp1d    = [0.25 8];
AmpSat1  = 24;

end; % AmpFlag
% ------------------


% ------------------
% Motor Dynamics
if MotFlag

% Q0
Elec0n   = [1];
Elec0d   = [0.0000873 1.13];
TConst0  = 0.0047;
BackEMF0 = 0.0048;

% Q1
Elec1n   = [1];
Elec1d   = [0.0000873 1.13];
TConst1  = 0.0047;
BackEMF1 = 0.0048;

end; % MotFlag
% ------------------


% ------------------
% Robot Dynamics
% Linear approximation of robot
if RobFlag

% Q0
Mech0n = [1];
Mech0d = [0.0000715797777778 0.00001123];

% Q1
Mech1n = [1];
Mech1d = [0.0000715797777778 0.00001123];

end; % RobFlag
% ------------------


% ------------------
% Sensor Dynamics
if SenFlag

% Q0
Sens0 = 1.1111;

% Q1
Sens1 = 1.1111;

end; % SenFlag
% ------------------