const fs = require('fs');
const jpeg = require('jpeg-js');
var image_path = process.argv[2] ? process.argv[2] : '';
var jpegData = fs.readFileSync(image_path);
var rawImageData = jpeg.decode(jpegData,true);
console.log(process.argv[2]);
//console.log(rawImageData);
var dimension = rawImageData.width * rawImageData.height;
var newdata = [];
var iter = 0;
for(let i=0;i<dimension;i++){
    var temp = [];
    for(let j=0;j<4;j++){
        temp.push(rawImageData.data[iter])
        iter++;
    }
    temp = temp.join(',');
    newdata.push(temp);
}
console.log(newdata);

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
fs.writeFile('rgb_new.txt', newdata.join('",""'), (err) => {
  if (err) throw err;
    console.log('The file has been saved yeah!');
 });