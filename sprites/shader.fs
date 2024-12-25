#version 330 core 
      
    out vec4 color;
     
    in vec2 fragTexCoord;           // Texture coordinates (sampler2D)
	in vec4 fragColor; 
	
	uniform float percentage; 
	uniform sampler2D u_Texture;
	
	void main() { 
		
		
		color =	texture(u_Texture,fragTexCoord);
		if(fragTexCoord.x>= (33.0/192.0) && (fragTexCoord.x<=(158.0/192.0))){
			if(fragTexCoord.y> (21.0/48.0) && (fragTexCoord.y<(27.0/48.0))){
				if(((fragTexCoord.x*192.0-33.0)/123.0)<=percentage){
					color = mix(vec4(0,5,0,1),color,0.9);
				}
			}
		}
		
	};
