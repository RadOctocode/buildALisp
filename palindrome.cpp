        int temp_x=x;
        int counter=0,limit,division; 
        while(temp_x!=0){
		    division=temp_x/10;
		    cout<<temp_x%10<<" ";
		    temp_x=division;
		    counter++;
	    }
        return true;
//prints backwards