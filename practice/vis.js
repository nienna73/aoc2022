d3 = require("d3@6");

height = 500;
n = 20;
m = 200;
k = 10;

x = d3.scaleLinear([0,m-1], [0, width]);
y = d3.scaleLinear([0,1], [height,0]);
z = d3.interpolateCool;

area = d3.area()
        .x((d, i) => x(i))
        .y0(d => y(d[0]))
        .y1(d => y(d[1]));

stack = d3.stack()
            .keys(d3.range(n))
            .offset(offset)
            .order(d3.stackOrderNone);

function bumps() {
    function bump(a, n) {
        const x = 1 / (0.1 + Math.random());
        const y = 2 * Math.random() - 0.5;
        const z = 10 / (0.1 + Math.random());
        for (let i = 0; i < n; ++i) {
          const w = (i / n - y) * z;
          a[i] += x * Math.exp(-w * w);
        }
      }
    return function bumps(n, m) {
        const a = [];
        for (let i = 0; i < n; ++i) a[i] = 0;
        for (let i = 0; i < m; ++i) bump(a, n);
        return a;
      };
}

function randomize() {
    const layers = stack(d3.transpose(Array.from({length, n}, () => bumps(m, k))));
    y.domain([
        d3.min(layers, l => d3.min(l, d => d[0])),
        d3.max(layers, l => d3.max(l, d => d[1]))
    ]);

    return layers;
}


function chart() {
    const svg = d3.create("svg").attr("viewBox", [0, 0, width, height]);

    const path = svg.selectAll("path")
                    .data(randomize)
                    .join("path")
                    .attr("d", area)
                    .attr("fill", () => z(Math.random()));

    while (true) {
        yield svg.node();

        await path
                .data(randomize)
                .transition()
                    .delay(1000)
                    .duration(1500)
                    .attr("d", area)
                .end();
    }
}

chart();