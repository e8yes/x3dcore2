function create_shader_from_code(code, ext)
{
    var shader;
    
    switch (ext) {
        case "glslf":
            shader = gl.createShader(gl.FRAGMENT_SHADER);
            break;
        case "glslv":
            shader = gl.createShader(gl.VERTEX_SHADER);
            break;
        default:
            alert("Incorrect extension " + ext);
            return null;
    }
    
    gl.shaderSource(shader,code);
    gl.compileShader(shader);

    if (!gl.getShaderParameter(shader,gl.COMPILE_STATUS)) {
        alert(gl.getShaderInfoLog(shader));
        return null;
    }

    return shader;
}

function create_shader_from_script_tag(sid) 
{
    var shaderScript = document.getElementById(sid);
    if (!shaderScript)
        return null;

    var str = "";
    var k = shaderScript.firstChild;
    while (k) {
        if (k.nodeType == 3)
            str += k.textContent;
        k = k.nextSibling;
    }

    var ext;
    if (shaderScript.type == "x-shader/x-fragment") {
        ext="glslf";
    } else if (shaderScript.type == "x-shader/x-vertex") {
        ext="glslv";
    } else {
        return null;
    }
    
    return create_shader_from_code(code,ext);
}

function last_after(s,stor)
{
    var c = s.split(stor);
    return c[c.length-1];
}

function create_shader_from_ext_script(sid)
{
    var path = document.getElementById(sid).src;
    if (!path) {
        alert("Shader script tag doesn't contain the source path (shouldn't import externally?).");
        return null;
    }
    
    var filename = last_after(path,"/");
    var ext = last_after(filename,".");
    var varname = filename.replace(".","");
    var code;
    try {
        code = eval(varname);
    } catch (e) {
        alert("Shader source file doesn't contain the string variable: " + varname + " or the shader script hasn't got loaded properly.");
        return null;
    }
    
    return create_shader_from_code(code,ext);
} 


function create_shader_program(vs_id, fs_id, is_ext=true) 
{
    var fs = is_ext ? create_shader_from_ext_script(fs_id) : create_shader_from_script_tag(fs_id);
    var vs = is_ext ? create_shader_from_ext_script(vs_id) : create_shader_from_script_tag(vs_id);
    var prog = gl.createProgram();
    
    gl.attachShader(prog, vs);
    gl.attachShader(prog, fs);
    gl.linkProgram(prog);

    if (!gl.getProgramParameter(prog, gl.LINK_STATUS)) {
        alert("Could not initialise shaders");
    }

    return prog;
}
