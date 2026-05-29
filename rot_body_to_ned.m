function [V_NED] = rot_body_to_ned(X)
    V_body = [X(1); X(2); X(3)]; % [u; v; w]
    
    roll = X(7);  % phi
    pitch = X(8); % theta
    yaw = X(9);   % psi
    
    c_phi = cos(roll);  s_phi = sin(roll);
    c_the = cos(pitch); s_the = sin(pitch);
    c_psi = cos(yaw);   s_psi = sin(yaw);
    
    % Matriz de Transformación estándar de Body a NED (R_b_to_n)
    R = [c_the*c_psi,  s_phi*s_the*c_psi - c_phi*s_psi,  c_phi*s_the*c_psi + s_phi*s_psi;
         c_the*s_psi,  s_phi*s_the*s_psi + c_phi*c_psi,  c_phi*s_the*s_psi - s_phi*c_psi;
         -s_the,       s_phi*c_the,                      c_phi*c_the];
    
    V_NED = R * V_body; % [x_dot; y_dot; z_dot]
end
