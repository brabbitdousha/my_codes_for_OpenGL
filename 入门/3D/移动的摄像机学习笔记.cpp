glm::vec3 cameraPos=glm::vec3(0.0f,0.0f,3.0f);
//摄像机位置
glm::vec3 cameraTarget=glm::vec3(0.0f,0.0f,0.0f);
glm::vec3 cameraDirection=glm::normalize(cameraPos-cameraTarget);
//我们希望方向向量指向摄像机的z轴方向
glm::vec3 up=glm::vec3(0.0f,1.0f,0.0f);
glm::vec3 cameraRight=glm::normalize(glm::cross(up,cameraDirection));
//定义一个上向量,然后和方向向量进行叉乘，得到指向x轴正方向的那个向量
glm::vec3 cameraUp=glm::cross(cameraDirection,cameraRight);
//把方向向量和右向量进行叉乘 得到上轴， 

glm::mat4 view;
view =glm::lookAt(glm::vec3(0.0f,0.0f,3.0f)),
      glm::vec3(0.0f,0.0f,0.0f),
	  glm::vec3(0.0f,1.0f,0.0f));
	  //摄像机位置，目标和上向量 （我们计算右向量使用的那个上向量）
	  
	  
	  float radius=10.0f;
	  float camX=sin(glfwGetTime())*radius;
	  float camZ=cos(glfwGetTime())*radius;
	  //glm::mat4 view;
	  view=glm::lookAt(glm::vec3(camX,0.0,camZ),glm::vec3(0.0,0.0,0.0), glm::vec3(0.0,1.0,0.0));
	  
	   glm::vec3 cameraPos=glm::vec3(0.0f,0.0f,3.0f);
	   glm::vec3 cameraFront=glm::vec3(0.0f,0.0f,-1.0f);
	   glm::vec3 cameraUp=glm::vec3(0.0f,1.0f,0.0f);
	   view=glm::lookAt(cameraPos,cameraPos+cameraFront,cameraUp);
	   
	   
	   float cameraSpeed=0.05f;
	   if(glfwGetKey(window,GLFW_KEY_W)==GLFW_PRESS)
	   cameraPos+=cameraSpeed*cameraFront;
	   if(glfwGetKey(window,GLFW_KEY_S)==GLFW_PRESS)
	   cameraPos-=cameraSpeed*cameraFront;
	   
	   if(glfwGetKey(window,GLFW_KEY_A)==GLFW_PRESS)
	    cameraPos-=glm::normalize(glm::cross(cameraFront,cameraUp))*cameraSpeed;
	   if(glfwGetKey(window,GLFW_KEY_D)==GLFW_PRESS)
	    cameraPos+=glm::normalize(glm::cross(cameraFront,cameraUp))*cameraSpeed;
	    //当我们按下WASD键的任意一个，摄像机的位置都会相应更新。如果我们希望向前或向后移动，
		//我们就把位置向量加上或减去方向向量。如果我们希望向左右移动，
		//我们使用叉乘来创建一个右向量(Right Vector)，并沿着它相应移动就可以了。
	     //注意这里的cameraFront和前面的位置向量是反的。 
