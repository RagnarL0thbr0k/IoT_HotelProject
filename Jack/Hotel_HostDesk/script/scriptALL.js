/**
 * Created by Utente on 17/07/2018.
 */
var dataRoom = new Array();
var dataHost = new Array();

var a = {
    "$class": "org.hotel.network.RoomBooking",
    "roomId": "resource:org.hotel.network.Room#P01R01",
    "guestId": "resource:org.hotel.network.HotelGuest#Gibbo_G",
    "permanence": "12-14/08/2018",
    "transactionId": "8d461b18311457d608d3646fec0b3d9d79f2f1731e732be2f6d5bc4b735a36a6",
    "timestamp": "2018-07-17T01:03:05.846Z"
};


function showALL() {


    try {

        $.get("http://40.114.200.254:3000/api/RoomBooking",function (data) {}).done(function (data) {

            for (var i = 0; i < data.length; i++){

                var id = data[i].roomId;
                var transaction = data[i].transactionId;
                var timestamp = data[i].timestamp;


                    dataRoom.push('<p>'+id+'/'+transaction+'/'+timestamp+'   '+'</p>');
                    Disp3(0);
            }

        }).fail(function() {
            alert( "Server is not online" );
        });


    }catch (error){
        alert("There is a server problem\n" + error);

    }

}

function showHost() {
    try {

        $.get("http://40.114.200.254:3000/api/HotelHost ",function (data) {}).done(function (data) {

            for (var i = 0; i < data.length; i++){

                var id = data[i].hostId;
                var name = data[i].firstName;
                var surname = data[i].lastName;
                var role = data[i].role;


                dataHost.push('<h6>'+id+'/'+name+'/'+surname+'/'+ role+'     '  +'</h6>');
                Disp3(1);
            }

        }).fail(function() {
            alert( "Server is not online" );
        });


    }catch (error){
        alert("There is a server problem\n" + error);

    }
}

function Disp3(identity) {
    var str='';
    var str2='';


    if (identity === 0){
        for (var i=0;i<dataRoom.length;i++)
        {
            str += dataRoom[i] +'<hr>';  // adding each element with key number to variable
        }

        document.getElementById('all_tran').innerHTML=str; // Display the elements of the array
    }
    if (identity === 1){
        for (var j=0;j<dataHost.length;j++)
        {
            str2 += dataHost[j] +'<hr>';  // adding each element with key number to variable
        }

        document.getElementById('all_host').innerHTML=str2; // Display the elements of the array
    }
}