#version 300 es

precision mediump float;

uniform sampler2D textureDiff;

uniform int blendState;

uniform vec3 matSpec, matAmbi, matEmit;
uniform float matSh;
uniform vec3 srcDiff, srcSpec, srcAmbi;

uniform vec3 lightDir;

in vec3 v_normal, v_view;
in vec2 v_texCoord;

layout(location = 0) out vec4 fragColor;

void main() {
    vec3 color = texture(textureDiff, v_texCoord).rgb;

    // 2. Implement Phong lighting
    // color = ;

    float alpha = 1.0f;

    // 4. Implement alpha blending
    // if (blendState == 0)
    //     alpha = ;
    // if (blendState == 1)
    //     alpha = ;
    // if (blendState == 2)
    //     alpha = ;

     fragColor = vec4(color, alpha);
}