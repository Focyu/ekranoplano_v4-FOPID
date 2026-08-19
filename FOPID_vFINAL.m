clearvars; close all; clc;
%% ============================================================
%% PARAMETROS GLOBALES DEL MODELO
%% ============================================================
Cp_motor = 0.57;
D_prop = 0.1270;
rho = 1.225;
Sp_prop = pi*(D_prop^2/4);
km_motor = 25.0;
Cp = Cp_motor;
D = D_prop;
Sp = pi*(D^2/4);
km = km_motor;
max_thrust_force_per_motor = 0.5*rho*Sp_prop*Cp_motor*km_motor^2;
fprintf('Thrust max por motor: %.3f N\n', max_thrust_force_per_motor);
fprintf('Thrust max total: %.3f N\n', 2*max_thrust_force_per_motor);

%% ============================================================
%% CONDICIONES INICIALES
%% ============================================================
tsim = 1;
step = 0.01;
x_nom = zeros(12,1);
x_nom(1) = 0.10;
x_nom(3) = 0.0;
x_nom(8) = 0.0;
x_nom(10) = 0.0;
x_nom(11) = 0.0;
x_nom(12) = -0.10;

u_nom = zeros(5,1);
u_nom(1) = 0.0;
u_nom(2) = 0.0;
u_nom(3) = 0.0;
u_nom(4:5) = 0.52;

x0 = zeros(12,1);

%% ============================================================
%% PARAMETROS DE CONTROL FOPID
%% ============================================================
u_sp = 20.0;
Kp_u = 2.0;
Ki_u = 1.0;
Kd_u = 0.0;

% 2. Lazo de Altura
h_sp    =  0.80;

Kp_h    =  0.50;
Ki_h    =  0.04;
Kd_h    =  0.01;


% 3. Lazo Interno de Elevador (Pitch)
Kp_pitch = -0.70;  
Ki_pitch = -0.08;
Kd_pitch = -0.01;


psi_sp = 0*(pi/180);
Kp_yaw = -1.0;
Ki_yaw = -0.50;
Kd_yaw = -0.0;


phi_sp = 0.0;
Kp_roll = -1.00;
Ki_roll = -0.50;
Kd_roll = -0.0;

%% ============================================================
%% SIMULACION (FORZANDO STOP TIME = tsim)
%% ============================================================
modelName = 'FOpid_control';
load_system(modelName);
set_param(modelName, 'StopTime', num2str(tsim));   % <-- FIX: fuerza tsim al modelo
out = sim(modelName);

%% ============================================================
%% LECTURA DE SEÑALES
%% ============================================================
if isprop(out,'tout')
    t = out.tout;
else
    error('No se encontro out.tout en la simulacion.');
end
S = read_sim_signal(out, 'states');
C = read_sim_signal(out, 'control_out');
LD_ratio = read_sim_signal(out, 'LD');
Fbx = read_sim_signal(out, 'Fbx');
Fby = read_sim_signal(out, 'Fby');
Fbz = read_sim_signal(out, 'Fbz');
Mx  = read_sim_signal(out, 'Mbx');
My  = read_sim_signal(out, 'Mby');
Mz  = read_sim_signal(out, 'Mbz');
CQ = read_sim_signal(out, 'CQ');
Cl = read_sim_signal(out, 'Cl');
Cn = read_sim_signal(out, 'Cn');
Cm = read_sim_signal(out, 'Cm');
alpha = read_sim_signal(out, 'alpha');
beta  = read_sim_signal(out, 'beta');
CL_w_OGE = read_sim_signal(out, 'CL_w_OGE');
CL_h_OGE = read_sim_signal(out, 'CL_h_OGE');
CL_w_IGE = read_sim_signal(out, 'CL_w_IGE');
CL_h_IGE = read_sim_signal(out, 'CL_h_IGE');
CD_iw_IGE = read_sim_signal(out, 'CD_iw_IGE');
CD_ih_IGE = read_sim_signal(out, 'CD_ih_IGE');
Fgx = read_sim_signal(out, 'Fgx');
Fgy = read_sim_signal(out, 'Fgy');
Fgz = read_sim_signal(out, 'Fgz');
Fax = read_sim_signal(out, 'Fax');
Fay = read_sim_signal(out, 'Fay');
Faz = read_sim_signal(out, 'Faz');
Ftx = read_sim_signal(out, 'Ftx');
Fty = read_sim_signal(out, 'Fty');
Ftz = read_sim_signal(out, 'Ftz');

P  = read_sim_signal(out, 'Power');
E  = read_sim_signal(out, 'Energy');
LT = read_sim_signal(out, 'Load_Torque');

% Señales de los lazos FOPID (nombres del modelo toworkspace)
sp_u     = read_sim_signal(out, 'u_set');
sp_h     = read_sim_signal(out, 'altura_sp');
sp_theta = read_sim_signal(out, 'theta_sp');
sp_yaw   = read_sim_signal(out, 'yaw_sp');
sp_roll  = read_sim_signal(out, 'roll_sp');
act_u     = read_sim_signal(out, 'estado_u');
act_z     = read_sim_signal(out, 'estado_z');
act_theta = read_sim_signal(out, 'estado_theta');
act_yaw   = read_sim_signal(out, 'estado_psi');
act_roll  = read_sim_signal(out, 'estado_phi');
fopid_u     = read_sim_signal(out, 'fopid_u');
fopid_h     = read_sim_signal(out, 'fopid_h');
fopid_theta = read_sim_signal(out, 'fopid_theta');
fopid_yaw   = read_sim_signal(out, 'fopid_yaw');
fopid_roll  = read_sim_signal(out, 'fopid_roll');

%% ============================================================
%% NORMALIZACION DE FORMATOS (CON SU PROPIO VECTOR DE TIEMPO)
%% ============================================================
t = force_column(t);
S = force_matrix_cols(S, 12, 'states');

% --- DIAGNOSTICO CRUDO DE control_out ANTES DE PROCESAR ---
C_raw_check = C;
if isa(C_raw_check,'timeseries')
    raw_sz = size(C_raw_check.Data);
elseif isstruct(C_raw_check)
    if isfield(C_raw_check,'signals') && isfield(C_raw_check.signals,'values')
        raw_sz = size(C_raw_check.signals.values);
    else
        raw_sz = size(C_raw_check);
    end
else
    raw_sz = size(C_raw_check);
end
fprintf('\n--- DIAGNOSTICO control_out (crudo, antes de normalizar) ---\n');
fprintf('Tamaño detectado: [%d %d]\n', raw_sz(1), raw_sz(min(2,numel(raw_sz))));

C = force_control_matrix(C, 'control_out');

% --- DIAGNOSTICO POST-NORMALIZACION: valores por columna ---
fprintf('\n--- DIAGNOSTICO control_out (tras force_control_matrix) ---\n');
fprintf('Tamaño de C: [%d %d]\n', size(C,1), size(C,2));
col_labels = {'delta_a (ailerón)','delta_e (elevador)','delta_r (timón)','delta_t1 (throttle1)','delta_t2 (throttle2)'};
for col = 1:size(C,2)
    fprintf('%-22s -> min=%.6g max=%.6g media=%.6g\n', col_labels{col}, min(C(:,col)), max(C(:,col)), mean(C(:,col)));
end

[LD_ratio, t_LD]       = force_column_time(LD_ratio, t);
[alpha, t_alpha]       = force_column_time(alpha, t);
[beta, t_beta]         = force_column_time(beta, t);
[P, t_P]               = force_column_time(P, t);
[E, t_E]               = force_column_time(E, t);
[LT, t_LT]             = force_column_time(LT, t);
[Fbx, t_Fbx] = force_column_time(Fbx, t); [Fby, t_Fby] = force_column_time(Fby, t); [Fbz, t_Fbz] = force_column_time(Fbz, t);
[Fax, t_Fax] = force_column_time(Fax, t); [Fay, t_Fay] = force_column_time(Fay, t); [Faz, t_Faz] = force_column_time(Faz, t);
[Ftx, t_Ftx] = force_column_time(Ftx, t); [Fty, t_Fty] = force_column_time(Fty, t); [Ftz, t_Ftz] = force_column_time(Ftz, t);
[Fgx, t_Fgx] = force_column_time(Fgx, t); [Fgy, t_Fgy] = force_column_time(Fgy, t); [Fgz, t_Fgz] = force_column_time(Fgz, t);
[Mx, t_Mx]  = force_column_time(Mx, t);  [My, t_My]  = force_column_time(My, t);  [Mz, t_Mz]  = force_column_time(Mz, t);
[CL_w_OGE, t_CLwOGE] = force_column_time(CL_w_OGE, t);
[CL_h_OGE, t_CLhOGE] = force_column_time(CL_h_OGE, t);
[CL_w_IGE, t_CLwIGE] = force_column_time(CL_w_IGE, t);
[CL_h_IGE, t_CLhIGE] = force_column_time(CL_h_IGE, t);
[CD_iw_IGE, t_CDiw]   = force_column_time(CD_iw_IGE, t);
[CD_ih_IGE, t_CDih]   = force_column_time(CD_ih_IGE, t);
[CQ, t_CQ] = force_column_time(CQ, t);
[Cl, t_Cl] = force_column_time(Cl, t);
[Cm, t_Cm] = force_column_time(Cm, t);
[Cn, t_Cn] = force_column_time(Cn, t);

sp_u = force_column(sp_u);
act_u = force_column(act_u);
sp_h = force_column(sp_h);
act_z = force_column(act_z);
sp_theta = force_column(sp_theta);
act_theta = force_column(act_theta);
sp_yaw = force_column(sp_yaw);
act_yaw = force_column(act_yaw);
sp_roll = force_column(sp_roll);
act_roll = force_column(act_roll);
fopid_u = force_column(fopid_u);
fopid_h = force_column(fopid_h);
fopid_theta = force_column(fopid_theta);
fopid_yaw = force_column(fopid_yaw);
fopid_roll = force_column(fopid_roll);

%% ============================================================
%% DIAGNOSTICO DE LONGITUDES (ANTES DE REMUESTREAR)
%% ============================================================
fprintf('\n--- LONGITUDES ORIGINALES DE SEÑALES DEL MODELO ---\n');
diag_names = {'t','states','control_out','LD_ratio','alpha','beta','P','E','LT', ...
    'Fbx','Fby','Fbz','Fax','Fay','Faz','Ftx','Fty','Ftz','Fgx','Fgy','Fgz', ...
    'Mx','My','Mz','CL_w_OGE','CL_h_OGE','CL_w_IGE','CL_h_IGE','CD_iw_IGE','CD_ih_IGE', ...
    'CQ','Cl','Cm','Cn'};
diag_lens = [length(t), size(S,1), size(C,1), length(LD_ratio), length(alpha), length(beta), ...
    length(P), length(E), length(LT), length(Fbx), length(Fby), length(Fbz), ...
    length(Fax), length(Fay), length(Faz), length(Ftx), length(Fty), length(Ftz), ...
    length(Fgx), length(Fgy), length(Fgz), length(Mx), length(My), length(Mz), ...
    length(CL_w_OGE), length(CL_h_OGE), length(CL_w_IGE), length(CL_h_IGE), ...
    length(CD_iw_IGE), length(CD_ih_IGE), length(CQ), length(Cl), length(Cm), length(Cn)];
for k = 1:numel(diag_names)
    fprintf('%-14s -> %d muestras\n', diag_names{k}, diag_lens(k));
end

%% ============================================================
%% REMUESTREO DE TODAS LAS SEÑALES AL VECTOR DE TIEMPO MAESTRO 't'
%% ============================================================
N_master = length(t);
t_model = t;

LD_model  = resample_to(t_LD, LD_ratio, t);
alpha_model = resample_to(t_alpha, alpha, t);
beta_model  = resample_to(t_beta, beta, t);
P_model  = resample_to(t_P, P, t);
E_model  = resample_to(t_E, E, t);
LT_model = resample_to(t_LT, LT, t);
Fbx_model = resample_to(t_Fbx, Fbx, t); Fby_model = resample_to(t_Fby, Fby, t); Fbz_model = resample_to(t_Fbz, Fbz, t);
Fax_model = resample_to(t_Fax, Fax, t); Fay_model = resample_to(t_Fay, Fay, t); Faz_model = resample_to(t_Faz, Faz, t);
Ftx_model = resample_to(t_Ftx, Ftx, t); Fty_model = resample_to(t_Fty, Fty, t); Ftz_model = resample_to(t_Ftz, Ftz, t);
Fgx_model = resample_to(t_Fgx, Fgx, t); Fgy_model = resample_to(t_Fgy, Fgy, t); Fgz_model = resample_to(t_Fgz, Fgz, t);
Mx_model = resample_to(t_Mx, Mx, t); My_model = resample_to(t_My, My, t); Mz_model = resample_to(t_Mz, Mz, t);
CL_w_OGE_model = resample_to(t_CLwOGE, CL_w_OGE, t);
CL_h_OGE_model = resample_to(t_CLhOGE, CL_h_OGE, t);
CL_w_IGE_model = resample_to(t_CLwIGE, CL_w_IGE, t);
CL_h_IGE_model = resample_to(t_CLhIGE, CL_h_IGE, t);
CD_iw_IGE_model = resample_to(t_CDiw, CD_iw_IGE, t);
CD_ih_IGE_model = resample_to(t_CDih, CD_ih_IGE, t);
CQ_model = resample_to(t_CQ, CQ, t);
Cl_model = resample_to(t_Cl, Cl, t);
Cm_model = resample_to(t_Cm, Cm, t);
Cn_model = resample_to(t_Cn, Cn, t);

S_model = S;

% --- FIX PRINCIPAL: remuestrear C si su longitud no coincide con N_master ---
if size(C,1) ~= N_master
    warning('control_out tiene %d muestras (esperadas %d). Se remuestreará al tiempo maestro.', size(C,1), N_master);
    t_C = linspace(0, t(end), size(C,1))';
    C_model = resample_matrix(t_C, C, t);
else
    C_model = C;
end

gama_model = S_model(:,8) - atan2(S_model(:,3), S_model(:,1));
Va_model = sqrt(S_model(:,1).^2 + S_model(:,2).^2 + S_model(:,3).^2);
do_model_plots = true;
fprintf('\nN_master (referencia de tiempo, tsim = %.1f s) = %d muestras\n', tsim, N_master);

%% ============================================================
%% RECORTES FOPID (usan el mismo vector maestro t)
%% ============================================================
N = N_master;
t_fopid = t;
if length(act_z) ~= N, act_z = resample_to((0:length(act_z)-1)'*step, act_z, t); end
if length(sp_u) ~= N, sp_u = resample_to((0:length(sp_u)-1)'*step, sp_u, t); end
if length(act_u) ~= N, act_u = resample_to((0:length(act_u)-1)'*step, act_u, t); end
if length(sp_h) ~= N, sp_h = resample_to((0:length(sp_h)-1)'*step, sp_h, t); end
if length(sp_theta) ~= N, sp_theta = resample_to((0:length(sp_theta)-1)'*step, sp_theta, t); end
if length(act_theta) ~= N, act_theta = resample_to((0:length(act_theta)-1)'*step, act_theta, t); end
if length(sp_yaw) ~= N, sp_yaw = resample_to((0:length(sp_yaw)-1)'*step, sp_yaw, t); end
if length(act_yaw) ~= N, act_yaw = resample_to((0:length(act_yaw)-1)'*step, act_yaw, t); end
if length(sp_roll) ~= N, sp_roll = resample_to((0:length(sp_roll)-1)'*step, sp_roll, t); end
if length(act_roll) ~= N, act_roll = resample_to((0:length(act_roll)-1)'*step, act_roll, t); end
if length(fopid_u) ~= N, fopid_u = resample_to((0:length(fopid_u)-1)'*step, fopid_u, t); end
if length(fopid_h) ~= N, fopid_h = resample_to((0:length(fopid_h)-1)'*step, fopid_h, t); end
if length(fopid_theta) ~= N, fopid_theta = resample_to((0:length(fopid_theta)-1)'*step, fopid_theta, t); end
if length(fopid_yaw) ~= N, fopid_yaw = resample_to((0:length(fopid_yaw)-1)'*step, fopid_yaw, t); end
if length(fopid_roll) ~= N, fopid_roll = resample_to((0:length(fopid_roll)-1)'*step, fopid_roll, t); end

act_h = -act_z;
err_u     = sp_u     - act_u;
err_h     = sp_h     - act_h;
err_theta = sp_theta - act_theta;
err_yaw   = sp_yaw   - act_yaw;
err_roll  = sp_roll  - act_roll;
S_fopid = S;

%% ============================================================
%% PLOTTING DEL MODELO GENERAL
%% ============================================================
if do_model_plots
    figure
    plot(t_model,LD_model(:,1))
    xlabel('t [s]'); ylabel('L/D'); title('LD ratio'); grid on
    figure
    subplot(2,1,1)
    plot(t_model,alpha_model(:,1))
    xlabel('t [s]'); ylabel('\alpha [rad]'); title('Angle of attack'); grid on
    subplot(2,1,2)
    plot(t_model,beta_model(:,1))
    xlabel('t [s]'); ylabel('\beta [rad]'); title('Side-slip Angle'); grid on
    figure
    subplot(3,1,1)
    plot(t_model,P_model(:,1),'LineWidth',1.2)
    xlabel('t[s]'); ylabel('P [kW]'); grid on; title('Power')
    subplot(3,1,2)
    plot(t_model,E_model(:,1),'LineWidth',1.2)
    xlabel('t[s]'); ylabel('E [kWh]'); grid on; title('Energy')
    subplot(3,1,3)
    plot(t_model,LT_model(:,1),'LineWidth',1.2)
    xlabel('t[s]'); ylabel('T_L [Nm]'); grid on; title('Load Torque')
    figure
    subplot(2,2,1)
    hold on
    plot(t_model,Fbx_model(:,1),'LineWidth',1.2)
    plot(t_model,Fby_model(:,1),'LineWidth',1.2)
    plot(t_model,Fbz_model(:,1),'LineWidth',1.2)
    hold off
    xlabel('t [s]'); ylabel('F_b [N]'); title('F_b'); legend('Fbx','Fby','Fbz'); grid on
    subplot(2,2,2)
    hold on
    plot(t_model,Fax_model(:,1),'LineWidth',1.2)
    plot(t_model,Fay_model(:,1),'LineWidth',1.2)
    plot(t_model,Faz_model(:,1),'LineWidth',1.2)
    hold off
    xlabel('t [s]'); ylabel('F_a [N]'); title('F_a'); legend('Fax','Fay','Faz'); grid on
    subplot(2,2,3)
    hold on
    plot(t_model,Ftx_model(:,1),'LineWidth',1.2)
    plot(t_model,Fty_model(:,1),'LineWidth',1.2)
    plot(t_model,Ftz_model(:,1),'LineWidth',1.2)
    hold off
    xlabel('t [s]'); ylabel('F_t [N]'); title('F_t'); legend('Ftx','Fty','Ftz'); grid on
    subplot(2,2,4)
    hold on
    plot(t_model,Fgx_model(:,1),'LineWidth',1.2)
    plot(t_model,Fgy_model(:,1),'LineWidth',1.2)
    plot(t_model,Fgz_model(:,1),'LineWidth',1.2)
    hold off
    xlabel('t [s]'); ylabel('F_g [N]'); title('F_g'); legend('Fgx','Fgy','Fgz'); grid on
    figure
    subplot(3,1,1)
    plot(t_model,Mx_model(:,1))
    xlabel('t [s]'); ylabel('M_b_x [N]'); title('M_b_x'); grid on
    subplot(3,1,2)
    plot(t_model,My_model(:,1))
    xlabel('t [s]'); ylabel('M_b_y [N]'); title('M_b_y'); grid on
    subplot(3,1,3)
    plot(t_model,Mz_model(:,1))
    xlabel('t [s]'); ylabel('M_b_z [N]'); title('M_b_z'); grid on
    sgtitle('Torque vector M_b')
    figure
    subplot(1,2,1)
    plot(t_model,CL_w_OGE_model(:,1))
    xlabel('t [s]'); ylabel('CL_w_{OGE}'); title('CL_w_{OGE}'); grid on
    subplot(1,2,2)
    plot(t_model,CL_h_OGE_model(:,1))
    xlabel('t [s]'); ylabel('CL_h_{OGE}'); title('CL_h_{OGE}'); grid on
    sgtitle('Aerodyn Coefficient from lift forces OGE')
    figure
    subplot(1,2,1)
    plot(t_model,CL_w_IGE_model(:,1))
    xlabel('t [s]'); ylabel('CL_w_{IGE}'); title('CL_w_{IGE}'); grid on
    subplot(1,2,2)
    plot(t_model,CL_h_IGE_model(:,1))
    xlabel('t [s]'); ylabel('CL_h_{IGE}'); title('CL_h_{IGE}'); grid on
    sgtitle('Aerodyn Coefficient from lift forces IGE')
    figure
    subplot(1,2,1)
    plot(t_model,CD_iw_IGE_model(:,1))
    xlabel('t [s]'); ylabel('CD_{iw}_{IGE}'); title('CD_{iw}_{IGE}'); grid on
    subplot(1,2,2)
    plot(t_model,CD_ih_IGE_model(:,1))
    xlabel('t [s]'); ylabel('CD_{ih}_{IGE}'); title('CD_{ih}_{IGE}'); grid on
    sgtitle('Aerodyn Coefficient from drag forces IGE')
    figure
    plot(t_model,CQ_model(:,1))
    xlabel('t [s]'); ylabel('C_Q'); title('Aerodyn Coefficient from side forces'); grid on
    figure
    subplot(3,1,1)
    plot(t_model,Cl_model(:,1))
    xlabel('t [s]'); ylabel('C_l'); title('C_l'); grid on
    subplot(3,1,2)
    plot(t_model,Cm_model(:,1))
    xlabel('t [s]'); ylabel('C_m'); title('C_m'); grid on
    subplot(3,1,3)
    plot(t_model,Cn_model(:,1))
    xlabel('t [s]'); ylabel('C_n'); title('C_n'); grid on
    sgtitle('Aerodyn Coeff from torques')
    figure
    plot(t_model,S_model(:,1),t_model,S_model(:,2),t_model,S_model(:,3))
    xlabel('t [s]'); ylabel('[m/s]'); title('Linear velocities'); grid on
    legend('u','v','w')
    figure
    plot(t_model,S_model(:,4),t_model,S_model(:,5),t_model,S_model(:,6))
    xlabel('t [s]'); ylabel('[rad/s]'); title('Angular velocities'); grid on
    legend('p','q','r')
    figure
    plot(t_model,S_model(:,7),t_model,S_model(:,8),t_model,S_model(:,9))
    xlabel('t [s]'); ylabel('[rad]'); title('Euler angles'); grid on
    legend('\phi','\theta','\psi')
    figure
    hold all
    plot(t_model,-S_model(:,12))
    xlabel('t[s]'); ylabel('h_{NED}[m]'); title('Height in NED'); grid on
    figure
    hold all
    plot(t_model,S_model(:,10))
    plot(t_model,S_model(:,11))
    plot(t_model,S_model(:,12))
    xlabel('t[s]'); ylabel('[m]'); title('Positions in NED')
    legend('x_{NED}','y_{NED}','z_{NED}'); grid on
    figure
    hold all
    plot3(S_model(1,10),S_model(1,11),-S_model(1,12),'rx')
    plot3(S_model(:,10),S_model(:,11),-S_model(:,12),'b')
    xlabel('x_{NED}'); ylabel('y_{NED}'); zlabel('h_{NED}')
    title('Trajectory in 3D'); grid on
    legend('(x_0,y_0,h_0)','(x(t),y(t),h(t))')
    figure
    plot(t_model,gama_model)
    xlabel('t [s]'); ylabel('\gamma [rad]'); title('Flight Path Angle \gamma'); grid on
    figure
    plot(t_model,Va_model)
    xlabel('t [s]'); ylabel('V_a [m/s]'); title('True Airspeed V_a'); grid on
    figure
    subplot(5,1,1)
    plot(t_model,fopid_roll*180/pi)
    xlabel('t [s]'); ylabel('\delta_a [deg]'); title('Aileron Deflection (FOPID roll)'); grid on
    subplot(5,1,2)
    plot(t_model,fopid_theta*180/pi)
    xlabel('t [s]'); ylabel('\delta_e [deg]'); title('Elevator Deflection (FOPID pitch)'); grid on
    subplot(5,1,3)
    plot(t_model,fopid_yaw*180/pi)
    xlabel('t [s]'); ylabel('\delta_r [deg]'); title('Rudder Deflection (FOPID yaw)'); grid on
    subplot(5,1,4)
    plot(t_model,C_model(:,4).*100./max_thrust_force_per_motor)
    xlabel('t [s]'); ylabel('\delta_{t1} [%]'); title('Throttle 1'); grid on
    subplot(5,1,5)
    plot(t_model,C_model(:,5).*100./max_thrust_force_per_motor)
    xlabel('t [s]'); ylabel('\delta_{t2} [%]'); title('Throttle 2'); grid on
end

%% ============================================================
%% PLOTS FOPID
%% ============================================================
figure
subplot(5,1,1)
plot(t_fopid,err_u)
xlabel('t [s]'); ylabel('e_u [m/s]'); title('Error Velocidad (u)'); grid on
subplot(5,1,2)
plot(t_fopid,err_h)
xlabel('t [s]'); ylabel('e_h [m]'); title('Error Altura (h)'); grid on
subplot(5,1,3)
plot(t_fopid,err_theta)
xlabel('t [s]'); ylabel('e_\theta [rad]'); title('Error Pitch (\theta)'); grid on
subplot(5,1,4)
plot(t_fopid,err_yaw)
xlabel('t [s]'); ylabel('e_\psi [rad]'); title('Error Yaw (\psi)'); grid on
subplot(5,1,5)
plot(t_fopid,err_roll)
xlabel('t [s]'); ylabel('e_\phi [rad]'); title('Error Roll (\phi)'); grid on
sgtitle('FOPID - Señales de Error')

figure
subplot(5,1,1)
plot(t_fopid,fopid_u)
xlabel('t [s]'); ylabel('out_u'); title('Salida FOPID Velocidad'); grid on
subplot(5,1,2)
plot(t_fopid,fopid_h)
xlabel('t [s]'); ylabel('out_h'); title('Salida FOPID Altura'); grid on
subplot(5,1,3)
plot(t_fopid,fopid_theta)
xlabel('t [s]'); ylabel('out_\theta'); title('Salida FOPID Pitch'); grid on
subplot(5,1,4)
plot(t_fopid,fopid_yaw)
xlabel('t [s]'); ylabel('out_\psi'); title('Salida FOPID Yaw'); grid on
subplot(5,1,5)
plot(t_fopid,fopid_roll)
xlabel('t [s]'); ylabel('out_\phi'); title('Salida FOPID Roll'); grid on
sgtitle('FOPID - Salidas de los Controladores')

if ~isempty(S_fopid) && size(S_fopid,2) >= 12
    figure
    subplot(5,1,1)
    plot(t_fopid,repmat(u_sp,N,1),'r--','LineWidth',1.2)
    hold on
    plot(t_fopid,S_fopid(:,1),'b','LineWidth',1.2)
    hold off
    xlabel('t [s]'); ylabel('u [m/s]'); title('Velocidad: Ref vs Actual')
    legend('u_{sp}','u'); grid on
    subplot(5,1,2)
    plot(t_fopid,repmat(h_sp,N,1),'r--','LineWidth',1.2)
    hold on
    plot(t_fopid,-S_fopid(:,12),'b','LineWidth',1.2)
    hold off
    xlabel('t [s]'); ylabel('h [m]'); title('Altura: Ref vs Actual')
    legend('h_{sp}','h'); grid on
    subplot(5,1,3)
    plot(t_fopid,zeros(N,1),'r--','LineWidth',1.2)
    hold on
    plot(t_fopid,S_fopid(:,8),'b','LineWidth',1.2)
    hold off
    xlabel('t [s]'); ylabel('\theta [rad]'); title('Pitch: Ref dinámica vs Actual')
    legend('\theta_{sp}(din)','\theta'); grid on
    subplot(5,1,4)
    plot(t_fopid,repmat(psi_sp,N,1),'r--','LineWidth',1.2)
    hold on
    plot(t_fopid,S_fopid(:,9),'b','LineWidth',1.2)
    hold off
    xlabel('t [s]'); ylabel('\psi [rad]'); title('Yaw: Ref vs Actual')
    legend('\psi_{sp}','\psi'); grid on
    subplot(5,1,5)
    plot(t_fopid,repmat(phi_sp,N,1),'r--','LineWidth',1.2)
    hold on
    plot(t_fopid,S_fopid(:,7),'b','LineWidth',1.2)
    hold off
    xlabel('t [s]'); ylabel('\phi [rad]'); title('Roll: Ref vs Actual')
    legend('\phi_{sp}','\phi'); grid on
    sgtitle('FOPID - Referencia vs Estado Actual de la Planta')
end

%% ============================================================
%% EXPORTAR SEÑALES FOPID A EXCEL
%% ============================================================
fname_fopid = 'FOpid_TURB_comb.xlsx';
if exist(fname_fopid, 'file') == 2
    delete(fname_fopid);
end
act_h_out = act_h;
fopid_table = table( ...
    t_fopid, ...
    sp_h, act_h_out, err_h, fopid_h, ...
    sp_roll, act_roll, err_roll, fopid_roll, ...
    sp_theta, act_theta, err_theta, fopid_theta, ...
    sp_yaw, act_yaw, err_yaw, fopid_yaw, ...
    sp_u, act_u, err_u, fopid_u, ...
    'VariableNames', { ...
    't', ...
    'sp_h', 'actual_h', 'error_h', 'fopid_h', ...
    'sp_roll', 'actual_roll', 'error_roll', 'fopid_roll', ...
    'sp_theta', 'actual_theta', 'error_theta', 'fopid_theta', ...
    'sp_yaw', 'actual_yaw', 'error_yaw', 'fopid_yaw', ...
    'sp_u', 'actual_u', 'error_u', 'fopid_u'});
writetable(fopid_table, fname_fopid, 'Sheet', 'FOPID_only');
fprintf('\nOK: Archivo Excel FOPID exportado: %s\n', fname_fopid);
fprintf('Incluye sp_*, actual_*, error_* y fopid_* para h, roll, theta, yaw, u.\n');

%% ============================================================
%% FUNCIONES LOCALES
%% ============================================================
function x = read_sim_signal(out, varName)
    if isprop(out, varName)
        x = out.(varName);
        return;
    end
    try
        x = out.get(varName);
        return;
    catch
    end
    error('No se encontro la variable "%s" en la salida de simulacion.', varName);
end

function v = force_column(v)
    if isa(v, 'timeseries')
        v = v.Data;
    end
    if isstruct(v)
        if isfield(v, 'signals') && isfield(v.signals, 'values')
            v = v.signals.values;
        elseif isfield(v, 'values')
            v = v.values;
        elseif isfield(v, 'Data')
            v = v.Data;
        end
    end
    v = squeeze(v);
    if isempty(v)
        v = [];
        return;
    end
    if isvector(v)
        v = v(:);
        return;
    end
    if size(v,2) == 2
        v = v(:,2);
        return;
    end
    if size(v,1) == 2 && size(v,2) > 2
        v = v(2,:).';
        return;
    end
    if size(v,2) == 1
        v = v(:);
        return;
    end
    v = v(:,1);
end

function [v, tv] = force_column_time(raw, t_ref)
    tv = [];
    if isa(raw, 'timeseries')
        tv = raw.Time;
        v = raw.Data;
    elseif isstruct(raw)
        if isfield(raw, 'time')
            tv = raw.time;
        end
        if isfield(raw, 'signals') && isfield(raw.signals, 'values')
            v = raw.signals.values;
        elseif isfield(raw, 'values')
            v = raw.values;
        elseif isfield(raw, 'Data')
            v = raw.Data;
        else
            v = raw;
        end
    else
        v = raw;
    end
    v = squeeze(v);
    if isvector(v)
        v = v(:);
    elseif size(v,2) == 2
        if isempty(tv), tv = v(:,1); end
        v = v(:,2);
    else
        v = v(:,1);
    end
    if isempty(tv)
        if length(v) == length(t_ref)
            tv = t_ref;
        else
            dt_ref = mean(diff(t_ref));
            tv = (0:length(v)-1)' * dt_ref;
        end
    end
    tv = tv(:);
end

function v_out = resample_to(t_src, v_src, t_dst)
    if length(t_src) == length(t_dst) && max(abs(t_src - t_dst)) < 1e-9
        v_out = v_src;
        return;
    end
    if length(t_src) < 2
        v_out = repmat(v_src(1), length(t_dst), 1);
        return;
    end
    v_out = interp1(t_src, v_src, t_dst, 'linear', 'extrap');
    v_out = v_out(:);
end

% NUEVA FUNCION: version matricial de resample_to (para C_model)
function M_out = resample_matrix(t_src, M_src, t_dst)
    if length(t_src) == length(t_dst) && max(abs(t_src - t_dst)) < 1e-9
        M_out = M_src;
        return;
    end
    if size(M_src,1) < 2
        M_out = repmat(M_src(1,:), length(t_dst), 1);
        return;
    end
    M_out = interp1(t_src, M_src, t_dst, 'linear', 'extrap');
end

function M = force_matrix_cols(M, expectedCols, varName)
    if isa(M, 'timeseries')
        M = M.Data;
    end
    if isstruct(M)
        if isfield(M, 'signals') && isfield(M.signals, 'values')
            M = M.signals.values;
        elseif isfield(M, 'values')
            M = M.values;
        elseif isfield(M, 'Data')
            M = M.Data;
        end
    end
    M = squeeze(M);
    if isempty(M)
        error('La variable %s esta vacia.', varName);
    end
    if isvector(M)
        if expectedCols == 1
            M = M(:);
            return;
        else
            error('La variable %s llego como vector y se esperaban %d columnas.', varName, expectedCols);
        end
    end
    if size(M,2) ~= expectedCols && size(M,1) == expectedCols
        M = M.';
    end
    if size(M,2) ~= expectedCols
        error('La variable %s no tiene %d columnas. Tamaño detectado: [%d %d].', ...
            varName, expectedCols, size(M,1), size(M,2));
    end
end

function C = force_control_matrix(C, varName)
    if isa(C, 'timeseries')
        C = C.Data;
    end
    if isstruct(C)
        if isfield(C, 'signals') && isfield(C.signals, 'values')
            C = C.signals.values;
        elseif isfield(C, 'values')
            C = C.values;
        elseif isfield(C, 'Data')
            C = C.Data;
        end
    end
    C = squeeze(C);
    if isempty(C)
        warning('La variable %s esta vacia. Se rellenara con ceros.', varName);
        C = zeros(0,5);
        return;
    end
    if isvector(C)
        v = C(:);
        warning('La variable %s llego como vector. Se convertira a matriz Nx5 con columnas faltantes en cero.', varName);
        C = [v, zeros(length(v),4)];
        return;
    end
    if size(C,2) ~= 5 && size(C,1) == 5
        C = C.';
    end
    if size(C,2) < 5
        warning('La variable %s tiene %d columnas. Se completara hasta 5 con ceros.', varName, size(C,2));
        C = [C, zeros(size(C,1), 5-size(C,2))];
        return;
    end
    if size(C,2) > 5
        warning('La variable %s tiene %d columnas. Se usaran solo las primeras 5.', varName, size(C,2));
        C = C(:,1:5);
    end
end

