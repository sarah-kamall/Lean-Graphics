
// Example one
// void main() {
//     // gl_FragColor = vec4(gl_FragCoord.xy / iResolution.xy, 0.0, 1.0); //rgba 
//     if(gl_FragCoord.x > iResolution.x * 0.5 + 10.0 * sin(gl_FragCoord.y * 0.1 + iTime * 2.0))
//         gl_FragColor = vec4(1.0, 0.5, 0.0, 1.0);
//     else
//         gl_FragColor = vec4(0.0, 0.5, 1.0, 1.0);
//     //drawing a circle
//     if(distance(gl_FragCoord.xy, iResolution.xy * 0.5) < 100.0) {
//         gl_FragColor = vec4(1.0, 1.0, 1.0, 1);

//     }
// }
// example two
#iChannel0 "pickle_cat.png"
#iChannel1 "picke_cat_heightmap.jpg"
vec2 cycle(float theta) {
    return vec2(cos(theta), sin(theta));
}
void main() {
    vec2 uv = gl_FragCoord.xy / iResolution.xy;
    float depth = texture(iChannel1, uv).r;
    //make image as large as the screen :: gets color and returns the same image color at x,y position
    gl_FragColor = texture(iChannel0, uv + depth * 0.02 * cycle(iTime * 2.0));
    gl_FragColor.rgb *= gl_FragColor.a; // makes background black 
}