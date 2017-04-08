var positionglslf = `
precision mediump float;

varying vec3 vPosition;             // Vertex position (camera space)
varying vec3 vNormal;               // Vertex normal (camera space)

void main(void) 
{
    // Dummy variable to ensure the use of all vertex attributes.
    vec4 zero = vec4(vPosition + vNormal - vPosition - vNormal, 0.0);
    gl_FragColor = zero + vec4(abs(vPosition),1.0);
}
`;
