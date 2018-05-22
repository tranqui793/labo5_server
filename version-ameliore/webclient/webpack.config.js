var webpack = require('webpack');
var path = require('path');
var WebpackNotifierPlugin = require('webpack-notifier');
var HtmlWebpackPlugin = require('html-webpack-plugin')
var TsConfigPathsPlugin = require('awesome-typescript-loader').TsConfigPathsPlugin;

module.exports = {
    // This option controls if and how source maps are generated: 
    // https://webpack.js.org/configuration/devtool/
    // https://survivejs.com/webpack/building/source-maps/
    devtool: 'source-map', // best quality, can be used for production   

    // The points to enter the application and start resolving modules (bundling)
    // The application can have multiple entries, and each entry can result
    // in multiple bundles. Entries are root modules (at the beginning of the 
    // dependency graph).
    // https://webpack.js.org/configuration/entry-context/
    // https://survivejs.com/webpack/appendices/glossary/#developing
    entry: [
        // Add the react hot loader entry point - this needs to come first (you might only want this in your dev config)
        // See procedure for react-hot-loader here: http://gaearon.github.io/react-hot-loader/getstarted/
        'react-hot-loader/patch',

        // entry point of the application
        './app/index.tsx'
    ],

    // Configuration for files emitted by webpack (bundles and assets)
    // https://webpack.js.org/configuration/output/
    output: {
        // output directory as an absolute path
        path: path.join(__dirname, 'dist'),

        // name of each output bundle (single one here)
        filename: 'bundle.js'
    },

    // A list of webpack plugins, which customize the build process in various ways
    // https://webpack.js.org/configuration/plugins/#plugins
    plugins: [
        // Emit module paths instead of numeric IDs 
        // https://survivejs.com/webpack/appendices/hmr/#making-the-module-ids-more-debuggable  
        new webpack.NamedModulesPlugin(),

        // Hot module reload plugin (HMR)
        // https://survivejs.com/webpack/appendices/hmr/#enabling-hmr
        new webpack.HotModuleReplacementPlugin(),

        // Html webpack plugins generates an HTML entry point to the application
        new HtmlWebpackPlugin({
            // Title of generated entry page
            title: 'PCO File Client',
            chunksSortMode: 'dependency',
            // Template page (contains the react application root element)
            template: path.resolve(__dirname, './app/index.ejs')
        }),

        // Issue OS notifications upon webpack build
        new WebpackNotifierPlugin({ alwaysNotify: true })
    ],

    // Change how modules are resolved
    // https://webpack.js.org/configuration/resolve/#resolve
    resolve: {
        // Automatically resolve certain extensions
        // (defaults to 'extensions: ['.js', '.json']')
        // https://webpack.js.org/configuration/resolve/#resolve-extensions
        // Add '.ts' and '.tsx' as resolvable extensions.
        extensions: ['.webpack.js', '.web.js', '.ts', '.tsx', '.js'],

        // Necessary to support tsconfig.json baseUrl parameter: 
        // https://github.com/s-panferov/awesome-typescript-loader#advanced-path-resolution-in-typescript-20
        plugins: [
            new TsConfigPathsPlugin({
                tsconfig: path.resolve(__dirname, '/tsconfig.json'),
                compiler: 'typescript'
            })
        ]
    },
    module: {
        loaders: [
            // All files with a '.ts' or '.tsx' extension will be handled by 'awesome-typescript-loader'.
            {
                test: /\.tsx?$/,
                loaders: [
                    'react-hot-loader/webpack',
                    'awesome-typescript-loader'
                ],
                exclude: path.resolve(__dirname, 'node_modules'),
                include: path.resolve(__dirname, 'app'),
            },
            // All output '.js' files will have any sourcemaps re-processed by 'source-map-loader'.
            {
                enforce: 'pre',
                test: /\.js$/,
                loader: 'source-map-loader'
            },
            // Css modules will be loader by 'css-loader'
            {
                test: /\.css$/,
                use: ['style-loader', 'css-loader']
            },
            // Other content is loader by url-loader
            {
                test: /\.(png|woff|woff2|eot|ttf|svg)$/,
                use: ['url-loader']
            }
        ]
    },

    devServer: {
        hot: true
    }
};