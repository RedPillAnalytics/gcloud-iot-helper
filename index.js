const rp = require('request-promise')
const channel = 'UChoXabQMSsYA8JRbZ_St65Q'
const key = '****************'

/**
 * Responds to any HTTP request that can provide a "message" field in the body.
 *
 * @param {!Object} req Cloud Function request context.
 * @param {!Object} res Cloud Function response context.
 */
exports.main = (req, res) => {
    rp({uri: `https://www.googleapis.com/youtube/v3/channels?part=statistics&id=${channel}&fields=items/statistics/subscriberCount&key=${key}`, json: true}).then((body) => {
        res.status(200).json(body)
    }).catch((error) => {
        console.error(error)
        res.status(500)
    })
}
