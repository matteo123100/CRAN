package progetto.CELLA;
simple CELLA
{
    parameters:
		@signal[delay](type = long);
		@statistic[delayStat](source = "delay";record = mean,vector;);
	gates:
		input in_packet;	
}