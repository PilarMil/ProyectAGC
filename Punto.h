
class Punto
{	
	private:
	  int x;
	  int y;
	  float r;
	  float g;
	  float b;
	
	public:
		
		Punto(){
			//posicion
			x=0;
			y=0;
		}
		
	  Punto(int x_, int y_, float r_, float g_, float b_){
	  	x = x_;
	    y = y_;
	    r = r_;
	    g = g_;
	    b = b_;
	  }	
	  void ColorRGB(float r_, float g_, float b_){
		    r = r_;
		    g = g_;
		    b = b_;
		}

	  	int getX(){
			return x;
		}
		int getY(){
			return y;
		}
		float getR(){
    	return r;
		}
	
		float getG(){
		    return g;
		}
		
		float getB(){
		    return b;
		}
		int setX(float x_){
			x=x_;
		}
		int setY(float y_){
			y=y_;
		}
		
		int set(float x_, float y_){
			x=x_;
			y=y_;
		}
		
};


