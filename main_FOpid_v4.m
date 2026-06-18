clear all; close all; clc;

%% PARAMETROS GLOBALES DEL MODELO
% Motor: 2204-2300KV 
Cp_motor = 0.57;
D_prop   = 0.1270;                       
rho      = 1.225;
Sp_prop  = pi*(D_prop^2/4);
km_motor = 25.0;
Cp = Cp_motor;   % alias para el bloque Simulink
D  = D_prop;     % alias para el bloque Simulink 
Sp = pi*(D^2/4);
km = km_motor;
max_thrust_force_per_motor = 0.5*rho*Sp_prop*Cp_motor*km_motor^2;
fprintf('Thrust max por motor: %.3f N\n', max_thrust_force_per_motor);
fprintf('Thrust max total:     %.3f N\n', 2*max_thrust_force_per_motor);

%% CONDICIONES INICIALES
tsim = 1;
step = 0.01;
x_nom = zeros(12,1);
% Velocidad y ángulo de trimado calculado
x_nom(1)  = 20.0;           % u [m/s] — velocidad crucero
x_nom(3)  = 0;              % w [m/s]
x_nom(8)  = 1.5*(pi/180);   % theta trimado (~1.5° con iw=1.5°)
% x_nom(8)  = 0;   % theta trimado (~1.5° con iw=1.5°)
x_nom(10) = 0;              % x_NED
x_nom(11) = 0;              % y_NED
x_nom(12) = -1.0;         % z_NED (altura = 0.55 m)

% Throttle inicial: calculado para equilibrar drag
u_nom = zeros(5,1);
u_nom(2)   = 0.0;   % Elevador neutro
u_nom(4:5) = 0.52;  % CORREGIDO: era 0.80 (sobreempujaba), ahora equilibrado
% x0 = x_nom;
x0 = zeros(12,1);   % todos los estados en cero al inicio

%% PARAMETROS DE CONTROL PID (Para modelo de 1.2 kg)
% lambda = 0.5;   mu = 0.5;   % Órdenes fraccionarios (fijos)

% 1. Lazo de Velocidad
u_sp    = 20.0;
Kp_u    =  1.50;   
Ki_u    =  1.0;   
Kd_u    =  0.0;



% 2. Lazo de Altura
h_sp    =  1.0;

Kp_h    =  1.15;   
Ki_h    =  0.008;   
Kd_h    =  0.0;


% 3. Lazo Interno de Elevador (Pitch)
Kp_pitch = -0.80;  
Ki_pitch = -0.01;
Kd_pitch = -0.01;


% theta_max =  0.10;   
% theta_min = -0.10;

% 4. Lazo de Timón (Yaw)
psi_sp   = 0*(pi/180);
Kp_yaw   = -1.3200;  
Ki_yaw   = -0.0800;  
Kd_yaw   = -2.6000;

% 5. Lazo de Alerones (Roll)
phi_sp   = 0.0;
Kp_roll  = -0.4400;  
Ki_roll  = -0.1000;  
Kd_roll  = -0.3000;

%% Simulation
sim = sim('FOpid_control_V4.slx');
S = sim.states;
t = sim.tout;
C = sim.control_out; 
LD_ratio = sim.LD;
Fbx = sim.Fbx; Fby = sim.Fby; Fbz = sim.Fbz;
Mx = sim.Mbx; My = sim.Mby; Mz = sim.Mbz;
CQ = sim.CQ; Cl = sim.Cl; Cn = sim.Cn; Cm = sim.Cm;
alpha = sim.alpha; beta = sim.beta;
CL_w_OGE = sim.CL_w_OGE; CL_h_OGE = sim.CL_h_OGE;
CL_w_IGE = sim.CL_w_IGE; CL_h_IGE = sim.CL_h_IGE;
CD_iw_IGE = sim.CD_iw_IGE; CD_ih_IGE = sim.CD_ih_IGE;
Fgx = sim.Fgx; Fgy = sim.Fgy; Fgz = sim.Fgz;
Fax = sim.Fax; Fay = sim.Fay; Faz = sim.Faz;
Ftx = sim.Ftx; Fty = sim.Fty; Ftz = sim.Ftz;
P = sim.Power; E = sim.Energy; LT = sim.Load_Torque;

%% VALIDACIÓN DE DIMENSIONES (PROTECCIÓN CONTRA EL ERROR DE PLOT)
t = t(:); % Forzar a que t sea vector columna

% Si S viene transpuesto de Simulink, lo corregimos
if size(S, 1) ~= length(t) && size(S, 2) == length(t)
    S = S';
end

% Encontrar la longitud mínima común entre todas las variables clave
N = min([length(t), size(S,1), size(C,1), length(LD_ratio), length(alpha)]);

% Recortar temporalmente los vectores para las gráficas a la longitud N
t         = t(1:N);
S         = S(1:N, :);
C         = C(1:N, :);
LD_ratio  = LD_ratio(1:N);
alpha     = alpha(1:N);
beta      = beta(1:N);
P         = P(1:N);
E         = E(1:N);
LT        = LT(1:N);
Fbx = Fbx(1:N); Fby = Fby(1:N); Fbz = Fbz(1:N);
Fax = Fax(1:N); Fay = Fay(1:N); Faz = Faz(1:N);
Ftx = Ftx(1:N); Fty = Fty(1:N); Ftz = Ftz(1:N);
Fgx = Fgx(1:N); Fgy = Fgy(1:N); Fgz = Fgz(1:N);
Mx = Mx(1:N); My = My(1:N); Mz = Mz(1:N);
CL_w_OGE = CL_w_OGE(1:N); CL_h_OGE = CL_h_OGE(1:N);
CL_w_IGE = CL_w_IGE(1:N); CL_h_IGE = CL_h_IGE(1:N);
CD_iw_IGE = CD_iw_IGE(1:N); CD_ih_IGE = CD_ih_IGE(1:N);
CQ = CQ(1:N); Cl = Cl(1:N); Cm = Cm(1:N); Cn = Cn(1:N);
% 
% %% Plotting
% % LD ratio
% figure
% plot(t,LD_ratio(:,1))
% xlabel('t [s]')
% ylabel('L/D')
% title('LD ratio')
% grid on
% 
% %-------------------Alpha and beta----------
% figure
% subplot(2,1,1)
% plot(t,alpha(:,1))
% xlabel('t [s]')
% ylabel('\alpha [rad]')
% title('Angle of attack')
% grid on
% 
% subplot(2,1,2)
% plot(t,beta(:,1))
% xlabel('t [s]')
% ylabel('\beta [rad]')
% title('Side-slip Angle')
% grid on
% 
% %-------------------Power, Energy & Load Torque-------------------
% figure
% subplot(3,1,1)
% plot(t,P(:,1),'LineWidth',1.2)
% xlabel('t[s]')
% ylabel('P [kW]')
% grid on
% title('Power')
% 
% subplot(3,1,2)
% plot(t,E(:,1),'LineWidth',1.2)
% xlabel('t[s]')
% ylabel('E [kWh]')
% grid on
% title('Energy')
% 
% subplot(3,1,3)
% plot(t,LT(:,1),'LineWidth',1.2)
% xlabel('t[s]')
% ylabel('T_L [Nm]')
% grid on
% title('Load Torque')
% 
% % ----------------forces and torques---------------------------------------------
% figure
% subplot(2,2,1)
% hold on
% plot(t,Fbx(:,1),'LineWidth',1.2)
% plot(t,Fby(:,1),'LineWidth',1.2)
% plot(t,Fbz(:,1),'LineWidth',1.2)
% hold off
% xlabel('t [s]')
% ylabel('F_b [N]')
% title('F_b')
% legend('Fbx','Fby','Fbz')
% grid on
% 
% subplot(2,2,2)
% hold on
% plot(t,Fax(:,1),'LineWidth',1.2)
% plot(t,Fay(:,1),'LineWidth',1.2)
% plot(t,Faz(:,1),'LineWidth',1.2)
% hold off
% xlabel('t [s]')
% ylabel('F_a [N]')
% title('F_a')
% legend('Fax','Fay','Faz')
% grid on
% 
% subplot(2,2,3)
% hold on
% plot(t,Ftx(:,1),'LineWidth',1.2)
% plot(t,Fty(:,1),'LineWidth',1.2)
% plot(t,Ftz(:,1),'LineWidth',1.2)
% hold off
% xlabel('t [s]')
% ylabel('F_t [N]')
% title('F_t')
% legend('Ftx','Fty','Ftz')
% grid on
% 
% subplot(2,2,4)
% hold on
% plot(t,Fgx(:,1),'LineWidth',1.2)
% plot(t,Fgy(:,1),'LineWidth',1.2)
% plot(t,Fgz(:,1),'LineWidth',1.2)
% hold off
% xlabel('t [s]')
% ylabel('F_g [N]')
% title('F_g')
% legend('Fgx','Fgy','Fgz')
% grid on
% 
% figure
% subplot(3,1,1)
% plot(t,Mx(:,1))
% xlabel('t [s]')
% ylabel('M_b_x [N]')
% title('M_b_x')
% grid on
% 
% subplot(3,1,2)
% plot(t,My(:,1))
% xlabel('t [s]')
% ylabel('M_b_y [N]')
% title('M_b_y')
% grid on
% 
% subplot(3,1,3)
% plot(t,Mz(:,1))
% xlabel('t [s]')
% ylabel('M_b_z [N]')
% title('M_b_z')
% grid on
% sgtitle('Torque vector M_b')
% 
% % ----------------Aerodyn Coeff---------------------------------------------
% figure
% subplot(1,2,1)
% plot(t,CL_w_OGE(:,1))
% xlabel('t [s]')
% ylabel('CL_w_{OGE}')
% title('CL_w_{OGE}')
% grid on
% 
% subplot(1,2,2)
% plot(t,CL_h_OGE(:,1))
% xlabel('t [s]')
% ylabel('CL_h_{OGE}')
% title('CL_h_{OGE}')
% grid on
% sgtitle('Aerodyn Coefficient from lift forces OGE')
% 
% figure
% subplot(1,2,1)
% plot(t,CL_w_IGE(:,1))
% xlabel('t [s]')
% ylabel('CL_w_{IGE}')
% title('CL_w_{IGE}')
% grid on
% 
% subplot(1,2,2)
% plot(t,CL_h_IGE(:,1))
% xlabel('t [s]')
% ylabel('CL_h_{IGE}')
% title('CL_h_{IGE}')
% grid on
% sgtitle('Aerodyn Coefficient from lift forces IGE')
% 
% figure
% subplot(1,2,1)
% plot(t,CD_iw_IGE(:,1))
% xlabel('t [s]')
% ylabel('CD_{iw}_{IGE}')
% title('CD_{iw}_{IGE}')
% grid on
% 
% subplot(1,2,2)
% plot(t,CD_ih_IGE(:,1))
% xlabel('t [s]')
% ylabel('CD_{ih}_{IGE}')
% title('CD_{ih}_{IGE}')
% grid on
% sgtitle('Aerodyn Coefficient from drag forces IGE')
% 
% %--------------------------------------------------------
% figure
% plot(t,CQ(:,1))
% xlabel('t [s]')
% ylabel('C_Q')
% title('C_Q')
% grid on
% title('Aerodyn Coefficient from side forces')
% 
% figure
% subplot(3,1,1)
% plot(t,Cl(:,1))
% xlabel('t [s]')
% ylabel('C_l')
% title('C_l')
% grid on
% 
% subplot(3,1,2)
% plot(t,Cm(:,1))
% xlabel('t [s]')
% ylabel('C_m')
% title('C_m')
% grid on
% 
% subplot(3,1,3)
% plot(t,Cn(:,1))
% xlabel('t [s]')
% ylabel('C_n')
% title('C_n')
% grid on
% sgtitle('Aerodyn Coeff from torques')
% 
% % ----------------States---------------------------------------------
% % Linear velocities (LÍNEA ORIGINAL CON ERROR, AHORA CORREGIDA)
% figure
% plot(t,S(:,1),t,S(:,2),t,S(:,3))
% xlabel('t [s]')
% ylabel('[m/s]')
% title('Linear velocities')
% grid on
% legend('u','v','w')
% 
% %-----------------------------angular velocities
% figure
% plot(t,S(:,4),t,S(:,5),t,S(:,6))
% xlabel('t [s]')
% ylabel('[rad/s]')
% title('Angular velocities')
% grid on
% legend('p','q','r')
% 
% %-----------------------Euler angles
% figure
% plot(t,S(:,7),t,S(:,8),t,S(:,9))
% xlabel('t [s]')
% ylabel('[rad]')
% title('Euler angles')
% grid on
% legend('\phi','\theta','\psi')
% 
% figure
% hold all
% plot(t,-S(:,12))
% xlabel('t[s]')
% ylabel('h_{NED}[m]')
% title('Height in NED')
% grid on
% 
% figure
% hold all
% plot(t,S(:,10))
% plot(t,S(:,11))
% plot(t,S(:,12))
% xlabel('t[s]')
% ylabel('[m]')
% title('Positions in NED')
% legend('x_{NED}','y_{NED}','z_{NED}')
% grid on
% 
% figure
% hold all
% plot3(S(1,10),S(1,11),-S(1,12),'rx')
% plot3(S(:,10),S(:,11),-S(:,12),'b')
% xlabel('x_{NED}')
% ylabel('y_{NED}')
% zlabel('h_{NED}')
% title('Trajectory in 3D')
% grid on
% legend('(x_0,y_0,h_0)','(x(t),y(t),h(t))')
% 
% %--------------other-----------------
% gama = S(:,8)-atan2(S(:,3),S(:,1));
% figure
% plot(t,gama)
% xlabel('t [s]')
% ylabel('\gamma [rad]')
% title('Flight Path Angle \gamma')
% grid on
% 
% Va = sqrt(S(:,1).^2+S(:,2).^2+S(:,3).^2);
% figure
% plot(t,Va)
% xlabel('t [s]')
% ylabel('V_a [m/s]')
% title('True Airspeed V_a')
% grid on
% 
% % ----------------Control---------------------------------------------
% figure
% subplot(5,1,1)
% plot(t,C(:,1))
% xlabel('t [s]')
% ylabel('\delta_a [deg]')
% title('Aileron Deflection')
% grid on
% 
% subplot(5,1,2)
% plot(t,C(:,2))
% xlabel('t [s]')
% ylabel('\delta_e [deg]')
% title('Elevator Deflection')
% grid on
% 
% subplot(5,1,3)
% plot(t,C(:,3))
% xlabel('t [s]')
% ylabel('\delta_r [deg]')
% title('Rudder Deflection')
% grid on
% 
% subplot(5,1,4)
% plot(t,C(:,4).*100./max_thrust_force_per_motor)
% xlabel('t [s]')
% ylabel('\delta_{t1} [%]')
% title('Throttle 1')
% grid on
% 
% subplot(5,1,5)
% plot(t,C(:,5).*100./max_thrust_force_per_motor)
% xlabel('t [s]')
% ylabel('\delta_{t2} [%]')
% title('Throttle 2')
% grid on