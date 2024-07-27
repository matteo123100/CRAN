package progetto.BBU;
simple BBU
{	parameters:
    	int M = default(10);
    	@signal[queueingTime](type = long);
		@statistic[queueingTime](source = "queueingTime";record = mean,vector;);
	gates:
		input in;
		output out[]; 
}