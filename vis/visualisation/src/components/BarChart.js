import React, {Component} from 'react';
import * as d3 from "d3";
import data from '../files/day8.json'

function getColor(d) {
  var g = 120;
  var b = g + (d * 7) % (256-g)
    
  return 'rgb(' + 0 + ',' + b + ',' + g + ')'
}

class BarChart extends Component {
    componentDidMount() {
      this.drawChart();
    }

    drawChart() {
      // set the dimensions and margins of the graph
      var margin = {top: 80, right: 30, bottom: 50, left:110}
      var width = 1000 - margin.left - margin.right;
      var height = 1000 - margin.top - margin.bottom;
      var offset = 10;
      var colors = []
      var indexes = []
      for (var n = 0; n < 99; n++) {
        colors.push(getColor(n));
        indexes.push(n);
      }
      var multiply = 100;
      var canvas = d3.select("body")
          .append("svg")
          .attr("width", width).attr("height", height);

      var dataArray = data[0];
      for (var m = 0; m < 99; m++) {
        dataArray = data[m];
        var color = colors[m];
        console.log(dataArray.items);

        canvas.selectAll("rect")
            .data(dataArray.values())
            .enter()
            .append("rect")
                .attr("width", function(d, i){
                    return d * 30;
                })
                .attr("height", 25)
                .attr("y", function(d,i) {
                  return i*35;
                })
                .attr("x", 0)
                .attr("fill", color);
          offset += 10;
          multiply -= 1;
        }
    }

    render(){
        return <div id={"#" + this.props.id}></div>
      }
  
  
}


export default BarChart;