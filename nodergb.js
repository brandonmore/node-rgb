const  serialport = require('serialport');
const fs = require('fs');
const jpeg = require('jpeg-js');
const packet_size = 7;
var myPort = new serialport('COM4', {
  baudRate: 9600
})
// serialport.list(function (err, ports) {
//   ports.forEach(function(port) {
//     console.log(port.comName);
//   });
// });

var image_path = process.argv[2] ? process.argv[2] : '';
var jpegData = fs.readFileSync(image_path);
var rawImageData = jpeg.decode(jpegData,true);
console.log(process.argv[2]);
//console.log(rawImageData);
var dimension = rawImageData.width * rawImageData.height;
var newdata = [];
var finaldata = [];
var iter = 0;
// for(let i=0;i<dimension;i++){
//     var temp = [];
//     for(let j=0;j<4;j++){
//         if(j<3)
//           temp.push(rawImageData.data[iter])
//         iter++;
//     }
//     temp = temp.join(',');
//     newdata.push(temp);
// }
for(let i=0;i<dimension;i++){
    var temp = [];
    for(let j=0;j<4;j++){
        if(j<3)
          newdata.push(rawImageData.data[iter])
        iter++;
    }
    //temp = temp.join(',');
    //newdata.push(temp);
}
let temp_arr = [];
let count = 1;
for(let i=0;i<newdata.length;i++){
    temp_arr.push(newdata[i]);
    if(count==packet_size*3){
        //console.log(temp_arr.length);
        finaldata.push(temp_arr.join(","));
        temp_arr = [];
        count=0;
    }
    count++;
}
//console.log(finaldata[0]);
//console.log(finaldata[0]);
var createPixel = (rgb) => {
  return '<span style="background-color:rgba('+rgb+')"></span>';
}
//console.log(jpegImageData);
var markup = "<html><body><style>div{overflow:hidden;}span{border:2px solid black;width:5px;height:5px;float:left;}</style><div>";
newdata.map((rgb,index)=>{
  if(index%rawImageData.width == 0)
    markup+='</div><div>';
  markup+=createPixel(rgb);
})
markup+='</div>';
markup+= '</body></html>';
fs.writeFile('rgb_new.html', markup, (err) => {
        if (err) throw err;
        console.log('The file has been saved yeah!');
      });
fs.writeFile('rgb_new.txt', newdata.join(','), (err) => {
  if (err) throw err;
    console.log('The file has been saved yeah!');
 });


//console.log(newdata[0]);
var iter = 0;
var inter = {};
setTimeout(function(){
    //myPort.write(finaldata[0]+"\n");
    inter = setInterval(function(){
        if(iter>=finaldata.length-1)
            clearInterval(inter);
        //console.log(finaldata[iter]);
        myPort.write(finaldata[iter]+"\n");
        iter++;

    },50);
},1000);