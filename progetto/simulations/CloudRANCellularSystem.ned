//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

package progetto.simulations;

import progetto.AS.*;
import progetto.BBU.*;
import progetto.CELLA.*;
import progetto.RRH.*;

network CloudRANCellularSystem
{
    parameters:
        int N = default(2);
        int test = default(0);
        int Percentuale_compressione=default(0);
        int lognormal_test = default(0)
        @display("bgb=1043,467");
    submodules:
        AS: AS {
            @display("p=107,390;is=vl");
        }
        BBU: BBU {
            @display("p=106.00875,172.755");
        }
        CELLA[N]: CELLA {
            @display("p=514.33875,172.755");
        }
        RRH[N]: RRH {
            @display("p=308.86502,172.755");
        }
    connections:



        AS.out --> BBU.in;
        for i=0..(N-1) {
            BBU.out++ --> RRH[i].in_packet;
            RRH[i].out_packet --> CELLA[i].in_packet;
        }
}
