% Script para documentar arquitectura, CÓDIGO y PARÁMETROS de Simulink
% Modelo: pid_control_V4

model_name = 'FOpid_RL';
load_system(model_name);

%% 1. EXTRACCIÓN DE BLOQUES
blocks = find_system(model_name, 'FindAll', 'on', 'Type', 'block');
fid1 = fopen('bloques_estables.txt', 'w');
for i = 1:length(blocks)
    try
        fprintf(fid1, '%s\n', getfullname(blocks(i)));
    catch
    end
end
fclose(fid1);

%% 2. EXTRACCIÓN DE CÓDIGO DE "MATLAB FUNCTIONS" (A OTRO TXT)
fid_code = fopen('codigo_funciones_matlab.txt', 'w');
fprintf(fid_code, '==========================================================\n');
fprintf(fid_code, 'REPORTE DE CÓDIGO INTERNO - MATLAB FUNCTIONS\n');
fprintf(fid_code, 'Modelo: %s\n', model_name);
fprintf(fid_code, 'Fecha: %s\n', datestr(now));
fprintf(fid_code, '==========================================================\n\n');

rt = sfroot;
all_charts = rt.find('-isa', 'Stateflow.EMChart');
encontrados = 0;

for i = 1:length(all_charts)
    if contains(all_charts(i).Path, model_name)
        try
            encontrados = encontrados + 1;
            funcPath = all_charts(i).Path;
            scriptContent = all_charts(i).Script;
            
            if iscell(scriptContent)
                scriptContent = strjoin(scriptContent, newline);
            end
            scriptContent = char(scriptContent);
            
            fprintf(fid_code, '----------------------------------------------------------\n');
            fprintf(fid_code, 'BLOQUE [%d]: %s\n', encontrados, funcPath);
            fprintf(fid_code, '----------------------------------------------------------\n');
            fprintf(fid_code, '%s\n\n', scriptContent);
        catch
        end
    end
end

if encontrados == 0
    fprintf(fid_code, 'AVISO: No se encontraron bloques de tipo MATLAB Function activos.\n');
end
fclose(fid_code);

%% 3. TAGS DE GOTO / FROM / TO WORKSPACE
fid2 = fopen('goto_from_tags_estables.txt', 'w');

% -- Extraer bloques Goto --
fprintf(fid2, '=== GOTO BLOCKS (Enviando señal) ===\n');
gotos = find_system(model_name, 'FindAll', 'on', 'BlockType', 'Goto');
for i = 1:length(gotos)
    try
        tag = get_param(gotos(i), 'GotoTag');
        name = getfullname(gotos(i));
        fprintf(fid2, '[GOTO] %s  ->  Tag: %s\n', name, tag);
    catch
    end
end

% -- Extraer bloques From --
fprintf(fid2, '\n=== FROM BLOCKS (Recibiendo señal) ===\n');
froms = find_system(model_name, 'FindAll', 'on', 'BlockType', 'From');
for i = 1:length(froms)
    try
        tag = get_param(froms(i), 'GotoTag'); 
        name = getfullname(froms(i));
        fprintf(fid2, '[FROM] %s  <-  Tag: %s\n', name, tag);
    catch
    end
end

% -- Extraer bloques To Workspace --
fprintf(fid2, '\n=== TO WORKSPACE BLOCKS (Guardando en Workspace) ===\n');
to_workspaces = find_system(model_name, 'FindAll', 'on', 'BlockType', 'ToWorkspace');
for i = 1:length(to_workspaces)
    try
        var_name = get_param(to_workspaces(i), 'VariableName'); 
        name = getfullname(to_workspaces(i));
        fprintf(fid2, '[TO WORKSPACE] %s  >>  Variable: %s\n', name, var_name);
    catch
    end
end
fclose(fid2);

%% 4. CONEXIONES DETALLADAS (VALORES DE CONSTANTES Y SIGNOS DE SUMA)
lines = find_system(model_name, 'FindAll', 'on', 'Type', 'line');
fid3 = fopen('conexiones_estables.txt', 'w');

for i = 1:length(lines)
    try
        % Obtener handles de puertos
        srcPortH = get_param(lines(i), 'SrcPortHandle');
        dstPortH = get_param(lines(i), 'DstPortHandle');
        
        % Obtener información del bloque de ORIGEN
        srcFullName = get_param(srcPortH, 'Parent');
        srcBlockType = get_param(srcFullName, 'BlockType');
        valInfo = '';
        
        % Si el origen es una CONSTANTE, extraer su valor
        if strcmp(srcBlockType, 'Constant')
            cVal = get_param(srcFullName, 'Value');
            valInfo = sprintf('{Val:%s}', cVal);
        end
        
        % Obtener nombre de la señal
        sig = get_param(lines(i), 'Name');
        
        % Lógica para eliminar "unnamed" e incluir valor de constante si aplica
        if isempty(sig) || (iscell(sig) && isempty(sig{1}))
            pathParts = split(srcFullName, '/');
            blockShortName = pathParts{end};
            pNum = get_param(srcPortH, 'PortNumber');
            sig = sprintf('sig_%s%s_p%d', blockShortName, valInfo, pNum);
        end
        
        if iscell(sig), sig = sig{1}; end
        srcPNum = get_param(srcPortH, 'PortNumber');
        
        % Procesar DESTINOS
        if iscell(dstPortH), targetPorts = [dstPortH{:}]; else, targetPorts = dstPortH; end
        
        for p = targetPorts
            dstFullName = get_param(p, 'Parent');
            dstBlockType = get_param(dstFullName, 'BlockType');
            dstPNum = get_param(p, 'PortNumber');
            sumSigns = '';
            
            % Si el destino es un SUMADOR, extraer los signos (ej: ++-)
            if strcmp(dstBlockType, 'Sum')
                signs = get_param(dstFullName, 'Inputs');
                sumSigns = sprintf(' [Signs:%s]', signs);
            end
            
            fprintf(fid3, '%s [Pin out:%d] --(%s)-- %s [Pin in:%d]%s\n', ...
                srcFullName, srcPNum, sig, dstFullName, dstPNum, sumSigns);
        end
    catch
    end
end
fclose(fid3);

%% 5. FINALIZACIÓN
disp('Documentación generada con éxito:');
disp('- bloques_estables.txt');
disp('- goto_from_tags_estables.txt (Goto, From y To Workspace incluidos)');
disp('- conexiones_estables.txt (Valores y Signos incluidos)');
disp('- codigo_funciones_matlab.txt');