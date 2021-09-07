glm::vec3 cameraPos=glm::vec3(0.0f,0.0f,3.0f);
//�����λ��
glm::vec3 cameraTarget=glm::vec3(0.0f,0.0f,0.0f);
glm::vec3 cameraDirection=glm::normalize(cameraPos-cameraTarget);
//����ϣ����������ָ���������z�᷽��
glm::vec3 up=glm::vec3(0.0f,1.0f,0.0f);
glm::vec3 cameraRight=glm::normalize(glm::cross(up,cameraDirection));
//����һ��������,Ȼ��ͷ����������в�ˣ��õ�ָ��x����������Ǹ�����
glm::vec3 cameraUp=glm::cross(cameraDirection,cameraRight);
//�ѷ������������������в�� �õ����ᣬ 

glm::mat4 view;
view =glm::lookAt(glm::vec3(0.0f,0.0f,3.0f)),
      glm::vec3(0.0f,0.0f,0.0f),
	  glm::vec3(0.0f,1.0f,0.0f));
	  //�����λ�ã�Ŀ��������� �����Ǽ���������ʹ�õ��Ǹ���������
	  
	  
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
	    //�����ǰ���WASD��������һ�����������λ�ö�����Ӧ���¡��������ϣ����ǰ������ƶ���
		//���ǾͰ�λ���������ϻ��ȥ�����������������ϣ���������ƶ���
		//����ʹ�ò��������һ��������(Right Vector)������������Ӧ�ƶ��Ϳ����ˡ�
	     //ע�������cameraFront��ǰ���λ�������Ƿ��ġ� 
