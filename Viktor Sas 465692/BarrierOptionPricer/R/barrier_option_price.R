#' European-style up-and-out 
#'
#' European-style up-and-out 
#' 
#'
#' @param nInt Number of time intervals
#' @param strike Strike price 
#' @param spot Spot price 
#' @param vol Volatility 
#' @param r Risk-free interest 
#' @param expiry Time to maturity 
#' @param barrier Barrier level 
#' @param nReps Number of Monte Carlo sim
#' @return The theoretical price
#' @examples
#' price <- barrier_option_price(126, 110, 105, 0.21, 0.05, 0.75, 120, 10000)
#' print(price)
#' @export
barrier_option_price <- function(nInt, strike, spot, vol, r, expiry, barrier, nReps) {
  result <- .Call('_BarrierOptionPricer_barrier_option_price', 
                  nInt, strike, spot, vol, r, expiry, barrier, nReps, 
                  PACKAGE = 'BarrierOptionPricer')
  return(result)
}