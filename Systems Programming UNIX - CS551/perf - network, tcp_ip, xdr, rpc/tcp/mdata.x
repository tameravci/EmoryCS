	struct manageData {
		int type; /* 1 for requesting range   compute >> manage
				   2 for requesting stats   report >> manage
				   3 terminate request      report >> manage
				   4 perfNumber submission  compute >> manage
				   5 numTested return        compute >> manage */
		int value;
		int time;
};


	struct computeData {
		int type; /* 1 for range 2 for numTested 3 for terminate */
		int start;
		int end;

	};


	struct range_entry {
		int start;
		int end;
	};

	struct reportData {
		char hostName[20];
		int fd;
		int perfArray[6];
		int perfIndex;
		int numTested;
		int numRange;
		int offset;
		range_entry rangeArray[1000];
	};



